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
            case sf::Key::A:
                move_dir.x = -1;
                break;
            case sf::Key::D:
                move_dir.x = 1;
                break;
            case sf::Key::W:
                move_dir.y = -1;
                break;
            case sf::Key::S:
                move_dir.y = 1;
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
            case sf::Key::A:
            case sf::Key::D:
                move_dir.x = 0;
                break;
            case sf::Key::W:
            case sf::Key::S:
                move_dir.y = 0;
                break;
            default:
                break;
        }
    }
    return true;
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

    if( move_dir != Vec2i::zero ) {
        Order order;
        order.type = Order::Move;
        order.move.x = move_dir.x;
        order.move.y = move_dir.y;
        SendOrder( order );
    }
}

