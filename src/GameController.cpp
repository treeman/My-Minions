#include "Tree/Game.hpp"
#include "Tree/Util.hpp"
#include "Tree/Log.hpp"
#include "GameController.hpp"
#include "World.hpp"

GameController::GameController( World *const _world ) :
    world( _world )
{
    SETTINGS->Register( "cam_nudge_speed", 500 );
}

bool GameController::HandleEvent( sf::Event &e )
{
    if( e.Type == sf::Event::KeyPressed ) {
        switch( e.Key.Code ) {
            case sf::Key::F10:
                GAME->Exit();
                break;
            case sf::Key::Left:
                cam_nudge_dir.x = -1;
                break;
            case sf::Key::Right:
                cam_nudge_dir.x = 1;
                break;
            case sf::Key::Up:
                cam_nudge_dir.y = -1;
                break;
            case sf::Key::Down:
                cam_nudge_dir.y = 1;
                break;
            default:
                break;
        }
    }
    else if( e.Type == sf::Event::KeyReleased ) {
        switch( e.Key.Code ) {
            case sf::Key::Left:
            case sf::Key::Right:
                cam_nudge_dir.x = 0;
                break;
            case sf::Key::Up:
            case sf::Key::Down:
                cam_nudge_dir.y = 0;
                break;
            default:
                break;
        }
    }
    return true;
}

Order GameController::Create( Order::OrderType type )
{
    const Vec2f mpos = Tree::GetMousePos();
    const Vec2i wpos = world->ConvertToWorld( mpos );

    Order order;
    order.type = type;
    order.pos.x = wpos.x;
    order.pos.y = wpos.y;

    return order;
}

void GameController::Update( float dt )
{
    if( cam_nudge_dir != Vec2i::zero ) {
        Order order;
        order.type = Order::CamNudge;
        const int cam_nudge_speed = SETTINGS->GetValue<int>( "cam_nudge_speed" );
        order.cam_nudge.x = cam_nudge_dir.x * cam_nudge_speed * dt;
        order.cam_nudge.y = cam_nudge_dir.y * cam_nudge_speed * dt;
        SendOrder( order );
    }

    if( Tree::GetInput().IsMouseButtonDown( sf::Mouse::Left ) ) {
        Order order = Create( Order::AddPath );
        SendOrder( order );
    }
    if( Tree::GetInput().IsMouseButtonDown( sf::Mouse::Right ) ) {
        SendOrder( Create( Order::RemovePath ) );
    }
    if( Tree::GetInput().IsKeyDown( sf::Key::Space ) ) {
        SendOrder( Create( Order::Chock ) );
    }
}

