#pragma once

#include <vector>

#include "Tree/InputHandler.hpp"
#include "Order.hpp"
#include "Controller.hpp"

class World;

class GameController : public Controller {
public:
    GameController( World *const world );

    bool HandleEvent( sf::Event &e );
    void Update( float dt );
protected:
    // Shortcut for simpler order sending
    void SendPos( Order::OrderType type );
    void SendSimple( Order::OrderType type );
    void SendSpeed( float speed );

    Vec2i cam_nudge_dir;
    World *const world;
};

