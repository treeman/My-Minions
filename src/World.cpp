#include <boost/foreach.hpp>

#include "Tree/Util.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Butler.hpp"
#include "World.hpp"

World::World() :
    //a full 800x600 screen
    grid( 19, 59, 40, 20 ),
    path( &grid ),
    is_running( true )
{
    CenterCam();
    SETTINGS->Register<bool>( "debug_mouse_grid_conversions", false );
    SETTINGS->Register<bool>( "debug_road_neighbours", false );

    hero.SetPos( grid.GridToPixelPos( 3, 3 ) );
}

void World::HandleOrder( Order order )
{
    const Vec2i wpos( order.pos.x, order.pos.y );
    const Vec2i gpos = grid.PixelToGridPos( wpos );

    if( order.type == Order::CamNudge ) {
        Vec2f new_cam = GetCamPos();
        new_cam = NudgeCamX( new_cam, order.cam_nudge.x );
        new_cam = NudgeCamY( new_cam, order.cam_nudge.y );
        UpdateCam( new_cam );
    }
    else if( order.type == Order::AddPath ) {
        if( gpos != invalid_grid_pos ) {
                path.Add( gpos );
        }
    }
    else if( order.type == Order::RemovePath ) {
        path.Remove( gpos );
    }
    else if( order.type == Order::Chock ) {
        path.Chock( gpos );
    }
    else if( order.type == Order::Pause ) {
        path.Pause();
        Pause();
    }
    else if( order.type == Order::Unpause ) {
        path.Start();
        Unpause();
    }
    else if( order.type == Order::TogglePause ) {
        TogglePause();
    }
}

Vec2f World::ConvertToWorld( Vec2f screen_pos ) const
{
    return Vec2f(
        screen_pos.x + cam.x,
        screen_pos.y + cam.y
    );
}

Vec2f World::ConvertToScreen( Vec2f world_pos ) const
{
    return Vec2f(
        world_pos.x - cam.x,
        world_pos.y - cam.y
    );
}

Vec2f World::GetCamPos() const
{
    return cam;
}

Vec2f World::NudgeCamX( Vec2f cam, int notches )
{
    cam.x += notches;
    return cam;
}

Vec2f World::NudgeCamY( Vec2f cam, int notches )
{
    cam.y += notches;
    return cam;
}

void World::CenterCam()
{
    const int window_w = Tree::GetWindowWidth();
    const int window_h = Tree::GetWindowHeight();

    CenterCamOn( window_w / 2, window_h / 2 );
}

void World::CenterCamOn( float x, float y )
{
    const int w = grid.PixelsWide();
    const int h = grid.PixelsHigh();

    Vec2f new_cam = GetCamPos();
    new_cam.x = w / 2 - x;
    new_cam.y = h / 2 - y;
    UpdateCam( new_cam );
}

void World::Update( float dt )
{
    grid.Update( dt );
    hero.Update( dt );
    path.Update( dt );

    if( SETTINGS->GetValue<bool>( "debug_mouse_grid_conversions" ) ) {
        const Vec2f mpos = Tree::GetMousePos();

        const Vec2f wpos = ConvertToWorld( mpos );
        const bool valid = grid.IsPosValid( wpos );
        const Vec2i gpos = grid.PixelToGridPos( wpos );

        const Vec2i tl = grid.TopLeftPos( gpos );
        const Vec2i tr = grid.TopRightPos( gpos );
        const Vec2i dl = grid.DownLeftPos( gpos );
        const Vec2i dr = grid.DownRightPos( gpos );

        std::stringstream ss;
        ss << "cam pos: " << cam;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "real mouse: " << mpos;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "world coords: " << wpos;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "valid grid?: " << valid;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "grid pos: " << gpos;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        if( valid ) {
            ss << "tl: " << tl << " tr: " << tr;
            Tree::VisualDebug( ss.str() );
            ss.str("");
            ss << "dl: " << dl << " dr: " << dr;
            Tree::VisualDebug( ss.str() );
            ss.str("");
        }

        if( path.Has( gpos ) ) { ss << "pathed"; }
        else { ss << "unpathed"; }
        Tree::VisualDebug( ss.str() );
        ss.str("");
    }
}

void World::Draw()
{
    grid.Draw();
    //hero.Draw();
    path.Draw( cam.x, cam.y );
}

void World::UpdateCam( Vec2f new_cam )
{
    const int move_x = cam.x - new_cam.x;
    const int move_y = cam.y - new_cam.y;
    cam = new_cam;

    hero.Move( move_x, move_y );
    grid.SetPos( cam.x, cam.y );
}

void World::Pause()
{
    path.Pause();
    is_running = false;
}
void World::Unpause()
{
    path.Start();
    is_running = true;
}
void World::TogglePause()
{
    if( is_running ) {
        Pause();
    }
    else {
        Unpause();
    }
}

