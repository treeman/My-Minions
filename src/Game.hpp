#pragma once

#include "Tree/Graphics.hpp"
#include "Tree/GameState.hpp"

#include "World.hpp"
#include "Controller.hpp"

class Game : public Tree::GameState {
public:
    Game();

    bool HandleEvent( sf::Event &e );

    void Loaded();

    void Update( float dt );
    void Draw();
private:
    sf::Sprite mouse;

    boost::shared_ptr<World> world;

    boost::shared_ptr<Controller> controller;

    Tree::InputChain input_chain;
};

