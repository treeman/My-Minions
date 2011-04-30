#pragma once

#include <vector>

#include "Tree/InputHandler.hpp"
#include "Order.hpp"
#include "Controller.hpp"

class World;

class GameController : public Controller {
public:
    GameController( World *const world);

    bool HandleEvent( sf::Event &e );
    void Update( float dt );
protected:
    Vec2i cam_nudge_dir;
    Vec2i move_dir;
    World *const world;
};
