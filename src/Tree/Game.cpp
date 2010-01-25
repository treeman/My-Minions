#include <time.h>

#include "Tree/Game.hpp"
#include "Tree/Settings.hpp"

using namespace Tree;

Game::Game() : exit_called( false )
{
	
}
Game::~Game()
{
	
}

bool Game::Logic()
{
	const float dt = hge->Timer_GetDelta();
	
	//set the new state to handle stuff
	curr_state = Top();
	
	if( curr_state ) {
		
		hgeInputEvent event;
		while( hge->Input_GetEvent( &event ) ) 
		{
			curr_state->HandleEvent( event );
		}
		
		curr_state->Update( dt );
	}
	
	return ShallExit();
}

bool Game::Render()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear( 0xFF000000 );
	
	if( curr_state ) curr_state->Render();

	hge->Gfx_EndScene();
	return false;
}

void Game::Init( int width, int height, bool windowed, std::string title, std::string settings_file )
{
	hge->System_SetState( HGE_DONTSUSPEND, true );
	hge->System_SetState( HGE_SHOWSPLASH, false );
	hge->System_SetState( HGE_HIDEMOUSE, true );
	
	hge->System_SetState( HGE_SCREENWIDTH, width );
	hge->System_SetState( HGE_SCREENHEIGHT, height );
	hge->System_SetState( HGE_WINDOWED, windowed );
	hge->System_SetState( HGE_SCREENBPP, 32 );
	hge->System_SetState( HGE_TITLE, title.c_str() );
	
	hge->Random_Seed( time( NULL ) );
	srand( time( NULL ) );
	
	if( settings_file != "" ) {
		try {
			SETTINGS->ParseFile( settings_file );
		}
		catch( Error::file_not_found &e ) { }
	}
}
void Game::InitPostHge()
{
	curr_state = Top();
}

void Game::Pop()
{
	state_list.pop_front();
}
void Game::Push( boost::shared_ptr<GameState> state )
{
	state_list.push_front( state );
}
boost::shared_ptr<GameState> Game::Top()
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
