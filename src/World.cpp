#include <boost/foreach.hpp>

#include "Tree/Util.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Butler.hpp"
#include "World.hpp"

World::World() :
    //a full 800x600 screen (tiles are 20x10)
    //grid( 39, 119, 20, 10 )
    grid( 19, 59, 40, 20 )
    //roughly half that then =)
    //grid( 20, 60, 20, 10 )
{
    CenterCam();
    SETTINGS->Register<bool>( "debug_mouse_grid_conversions", false );
    SETTINGS->Register<bool>( "debug_road_neighbours", false );
}

void World::HandleOrder( Order order )
{
    if( order.type == Order::CamNudge ) {
        NudgeCamX( order.cam_nudge.x );
        NudgeCamY( order.cam_nudge.y );
        UpdateCam();
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

void World::NudgeCamX( int notches )
{
    cam.x += notches;
}

void World::NudgeCamY( int notches )
{
    cam.y += notches;
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

    cam.x = w / 2 - x;
    cam.y = h / 2 - y;
    UpdateCam();
}
void World::Update( float dt )
{
    grid.Update( dt );

    const Vec2f mpos = Tree::GetMousePos();

    const Vec2f wpos = ConvertToWorld( mpos );
    const bool valid = grid.IsPosValid( wpos );
    const Vec2i gpos = grid.PixelToGridPos( wpos );

    const Vec2i tl = grid.TopLeftPos( gpos );
    const Vec2i tr = grid.TopRightPos( gpos );
    const Vec2i dl = grid.DownLeftPos( gpos );
        const Vec2i dr = grid.DownRightPos( gpos );

    if( SETTINGS->GetValue<bool>( "debug_mouse_grid_conversions" ) ) {
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
    }
}

void World::Draw()
{
    grid.Draw();
}

void World::UpdateCam()
{
    grid.SetPos( cam.x, cam.y );
}

