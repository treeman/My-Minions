#pragma once

#include <vector>

#include "Tree/InputHandler.hpp"
#include "Order.hpp"
#include "Controller.hpp"
#include "PathObject.hpp"

class World;

class GameController : public Controller {
public:
    GameController( World *const world );

    void Done();

    bool HandleEvent( sf::Event &e );

    void Update( float dt );
    void Draw();
protected:
    // Shortcut for simpler order sending
    void SendPos( Order::OrderType type );
    void SendSimple( Order::OrderType type );
    void SendSpeed();

    void SendPlacement();

    Vec2i cam_nudge_dir;

    World *const world;
    int curr_obj;

    int curr_speed;

    Tree::Timer del_t;
    Tree::Timer place_t;

    PathObjPtr obj;
    sf::Sprite obj_spr;
};

