#pragma once

#include "Tree/GameState.hpp"
#include "Tree/Timer.hpp"
#include "Tree/Graphics.hpp"

#include "Narrative.hpp"

class Intro : public Tree::GameState {
public:
    Intro();
    ~Intro();

    bool HandleEvent( sf::Event &e );

    void Loaded();

    void Update( float dt );
    void Draw();
private:
    Narrative narrative;
};

