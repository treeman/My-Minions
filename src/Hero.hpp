#pragma once

#include "Tree/Graphics.hpp"
#include "MoveableObject.hpp"

class Hero : public MoveableObject {
public:
    Hero();

    void Update( float dt );
private:
    void NewPos( Vec2i pos );

    void Render();

    sf::Sprite spr;
};

