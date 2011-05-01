#include <sstream>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "Tree/Game.hpp"
#include "Tree/Log.hpp"

using Tree::Game;

Game::Game() : exit_called( false ), state_changed( true ),
    fps( 0 ), fps_buff( 0 ), fps_frame_count( 0 ),
    drawn_lazy( false ), need_redraw( false )
{
    settings.reset( new Settings() );
    input_chain.reset( new InputChain() );
    butler.reset( new Butler() );
    tweaks.reset( new Tweaks() );
    log_helper.reset( new LogHelper() );
}
Game::~Game()
{
    L_ << "The game is destroyed\n";
}

void Game::Draw( const sf::Drawable &obj )
{
    window->Draw( obj );
}

void Game::PortionRedrawn( const Tree::Rect &rect )
{
    portions_redrawn.push_back( rect );
}
void Game::ClearWindow( const sf::Color color )
{
    shall_clear_window = true;
    need_redraw = true;
}
bool Game::NeedRedraw() const
{
    return need_redraw;
}
bool Game::NeedRedraw( const Tree::Rect &rect ) const
{
    for( Rects::const_iterator it = portions_redrawn.begin();
         it != portions_redrawn.end(); ++it )
    {
        if( it->Intersects( rect ) ) { return true; }
    }
    return false;
}

void Game::DrawLazy()
{
    drawn_lazy = true;
    portions_redrawn.clear();
}
void Game::DrawNormal()
{
    drawn_lazy = false;
}
bool Game::DrawingLazy()
{
    return drawn_lazy;
}

float Game::GetFPS()
{
    return fps;
}
const sf::Input &Game::GetInput()
{
    return window->GetInput();
}

Vec2f Game::GetMousePos() const
{
    return mpos;
}

void Game::SetMousePos( float x, float y )
{
    window->SetCursorPosition( x, y );
    mpos.x = x; mpos.y = y;
}

void Game::Init(
    int width,
    int height,
    bool windowed,
    std::string title,
    std::string settings_file,
    bool _drawn_lazy
) {
    srand( time( NULL ) );

    drawn_lazy = _drawn_lazy;

    TWEAKS->Load( "magic_numbers.lua" );

    settings->SetValue( "video_screen_width", width );
    settings->SetValue( "video_screen_height", height );
    settings->SetValue( "video_screen_windowed", windowed );

    settings->SetValue( "sound_enabled", true );
    settings->SetValue( "stream_volume", 100 );
    settings->SetValue( "music_volume", 100 );
    settings->SetValue( "effect_volume", 100 );

    if( settings_file != "" ) {
        try {
            settings->ParseFile( settings_file );
        }
        catch( Error::resource_not_found &e ) {
            L_ << "Oops, you've deleted the settings file '" + settings_file + "'\n";
            L_ << "God will not forgive you!!! :@\n";
            L_ << "Well... I'll just recreate it for you then I guess\n";

            settings->CreateSettingsFile( settings_file );
            settings->ParseFile( settings_file );
        }
    }

    settings->SetValue( "video_screen_bpp", 32 );
    settings->SetValue( "video_caption_title", title );

    window_manager.reset( new Tree::WindowManager() );
    window = window_manager->GetWindow();

    console.reset( new Tree::Console() );
    console->SetPriority( 0 );
    input_chain->AddHandler( console.get() );

    console->AddHistory( "starting up the ownage game environment" );
    console->AddHistory( "screen res: " +
        settings->GetSetting( "video_screen_width" ) + "x" +
        settings->GetSetting( "video_screen_height" ) + " bpp: " +
        settings->GetSetting( "video_screen_bpp" )
    );

    game_debug.reset( new Tree::GameDebug() );
    input_chain->AddHandler( game_debug.get() );

    visual_debug.reset( new Debug() );

    window->SetFramerateLimit( 100 );
}

void Game::Start()
{
    if( ShallExit() ) return;

    sf::Font fnt;

    curr_state = Top();

    while( window->IsOpened() )
    {
        //if we change state, change it now and not in the middle of things
        if( state_changed ) {
            curr_state->Unloaded();

            curr_state = Top();
            curr_state->Loaded();

            state_changed = false;
        }

        const float dt = window->GetFrameTime();
        UpdateFPS( dt );

        visual_debug->ResetTempStrings();

        sf::Event event;
        while( window->GetEvent( event ) )
        {
            if( event.Type == sf::Event::MouseMoved ) {
                mpos.x = event.MouseMove.X;
                mpos.y = event.MouseMove.Y;
            }

            //pass down events in a chain
            if( input_chain->HandleEvent( event ) ) {
                curr_state->HandleEvent( event );
            }

            //if we close the window, quit gracefully
            if( event.Type == sf::Event::Closed ) {
                Exit();
                break;
            }
        }

        curr_state->Update( dt );
        console->Update( dt );
        game_debug->Update( dt );

        //exit as fast as we can, no need to render if we want to quit
        if( ShallExit() ) {
            window->Close();
        }

        //begin render loop
        if( !drawn_lazy || shall_clear_window ) {
            window->Clear( sf::Color() );
            shall_clear_window = false;
        }

        curr_state->Draw();
        game_debug->Draw();
        visual_debug->Draw();
        console->Draw();

        //actually draw everything
        window->Display();

        //necessary to call it here so we can log rendering stuff too
        //this will simply reset the one time frame log
        log_helper->EndofLoop();

        //update lazy rendering
        if( drawn_lazy ) {
            need_redraw = false;
            portions_redrawn.clear();
        }
    }
}

void Game::Pop()
{
    state_list.pop_front();
    state_changed = true;
}
void Game::Push( boost::shared_ptr<GameState> state )
{
    state_list.push_front( state );
    state_changed = true;
}
boost::shared_ptr<Tree::GameState> Game::Top()
{
    if( !state_list.empty() ) {
        return state_list.front();
    }
    else {
        boost::shared_ptr<GameState> empty;
        return empty;
    }
}

void Game::Exit()
{
    exit_called = true;
}
bool Game::ShallExit() const
{
    return state_list.empty() || exit_called;
}

void Game::UpdateFPS( float dt )
{
    //simply update each second
    //no need for anything more sophisticated
    fps_buff += dt;
    ++fps_frame_count;
    if( fps_buff > 1.0 ) {
        fps = fps_frame_count / fps_buff;
        fps_buff = fps_frame_count = 0;
    }
}

