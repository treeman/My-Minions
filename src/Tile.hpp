#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Graphics.hpp"
#include "Tree/Vec2D.hpp"
#include "Tree/DrawnLazy.hpp"
#include "VisualObject.hpp"

class Tile : public VisualObject {
public:
    Tile( sf::Sprite base_spr, Vec2i pos, int width, int height, Vec2i grid_pos );

    Vec2i GetGridPos();

    void Update( float dt );
private:
    void NewPos( Vec2i pos );

    void Render();

    sf::Sprite base;

    int w, h;
    Vec2i grid_pos;

    sf::Sprite highlight;
};

typedef boost::shared_ptr<Tile> TilePtr;

