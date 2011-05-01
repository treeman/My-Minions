#include "Tree/Game.hpp"
#include "Tree/Util.hpp"
#include "Tree/Log.hpp"
#include "GameController.hpp"
#include "World.hpp"
#include "ObjectFactory.hpp"

GameController::GameController( World *const _world ) :
    world( _world ), curr_obj( 0 )
{
    SETTINGS->Register( "cam_nudge_speed", 500 );

    // Speed intervals of 1 to 9
    curr_speed = 3;

    SendSpeed();
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

            case sf::Key::Space:
                SendPos( Order::Chock );
                break;

            case sf::Key::P:
                SendSimple( Order::TogglePause );
                break;
            case sf::Key::Num1:
                curr_obj = 0;
                break;
            case sf::Key::Num2:
                curr_obj = 1;
                break;
            case sf::Key::Num3:
                curr_obj = 2;
                break;
            case sf::Key::Num4:
                curr_obj = 3;
                break;
            case sf::Key::Num5:
                curr_obj = 4;
                break;
            case sf::Key::Num6:
                curr_obj = 5;
                break;
            case sf::Key::Num7:
                curr_obj = 6;
                break;
            case sf::Key::Num8:
                curr_obj = 7;
                break;
            case sf::Key::Num9:
                curr_obj = 8;
                break;
            case sf::Key::Num0:
                curr_obj = 9;
                break;

            case sf::Key::LControl:
                if( curr_speed > 1 ) curr_speed--;
                SendSpeed();
                break;
            case sf::Key::LShift:
                if( curr_speed < 9 ) curr_speed++;
                SendSpeed();
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

void GameController::Update( float dt )
{
    const Vec2f mpos = Tree::GetMousePos();
    const Vec2i wpos = world->ConvertToWorld( mpos );

    if( cam_nudge_dir != Vec2i::zero ) {
        Order order;
        order.type = Order::CamNudge;
        const int cam_nudge_speed = SETTINGS->GetValue<int>( "cam_nudge_speed" );
        order.cam_nudge.x = cam_nudge_dir.x * cam_nudge_speed * dt;
        order.cam_nudge.y = cam_nudge_dir.y * cam_nudge_speed * dt;
        SendOrder( order );
    }

    if( Tree::GetInput().IsMouseButtonDown( sf::Mouse::Left ) ) {
        if( curr_obj == 0 ) {
            SendPos( Order::AddPath );
        }
        else {
            //L_ << "I want to build an object of type: " << curr_obj << '\n';
            Order order;
            order.type = Order::PlaceObject;
            order.object.x = wpos.x;
            order.object.y = wpos.y;
            order.object.obj = curr_obj;

            SendOrder( order );
        }
    }
    if( Tree::GetInput().IsMouseButtonDown( sf::Mouse::Right ) ) {
        SendPos( Order::RemovePath );
    }
}

void GameController::SendPos( Order::OrderType type )
{
    const Vec2f mpos = Tree::GetMousePos();
    const Vec2i wpos = world->ConvertToWorld( mpos );

    Order order;
    order.type = type;
    order.pos.x = wpos.x;
    order.pos.y = wpos.y;

    SendOrder( order );
}

void GameController::SendSimple( Order::OrderType type )
{
    Order order;
    order.type = type;
    SendOrder( order );
}

void GameController::SendSpeed()
{
    Order order;
    order.type = Order::SetSpeed;
    const float clock_time = TWEAKS->GetNum( "clock_time" );
    switch( curr_speed ) {
        case 1:
            order.sim_speed = TWEAKS->GetNum( "clock1" ) * clock_time;
            break;
        case 2:
            order.sim_speed = TWEAKS->GetNum( "clock2" ) * clock_time;
            break;
        case 3:
            order.sim_speed = TWEAKS->GetNum( "clock3" ) * clock_time;
            break;
        case 4:
            order.sim_speed = TWEAKS->GetNum( "clock4" ) * clock_time;
            break;
        case 5:
            order.sim_speed = TWEAKS->GetNum( "clock5" ) * clock_time;
            break;
        case 6:
            order.sim_speed = TWEAKS->GetNum( "clock6" ) * clock_time;
            break;
        case 7:
            order.sim_speed = TWEAKS->GetNum( "clock7" ) * clock_time;
            break;
        case 8:
            order.sim_speed = TWEAKS->GetNum( "clock8" ) * clock_time;
            break;
        case 9:
            order.sim_speed = TWEAKS->GetNum( "clock9" ) * clock_time;
            break;
    }
    SendOrder( order );
}

