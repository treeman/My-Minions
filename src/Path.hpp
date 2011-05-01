#pragma once

#include <set>
#include <list>

#include "Tree/Graphics.hpp"
#include "Tree/Vec2D.hpp"

#include "IsoGrid.hpp"

struct Charge {
    Vec2i point;
    Vec2i dir;
    Timer t;
};

class Path {
public:
    Path( IsoGrid *const grid );

    bool Has( Vec2i point );

    void Add( Vec2i point );
    void Add( int x, int y ) { Add( Vec2i( x, y ) ); }

    void Remove( Vec2i point );
    void Remove( int x, int y ) { Remove( Vec2i( x, y ) ); }

    void Chock( Vec2i point );

    void Draw( int x_off, int y_off );
private:
    typedef std::set<Vec2i> Points;
    Points points;

    typedef std::list<Charge> Charges;
    Charges charges;

    sf::Sprite spr;
    sf::Sprite charge;

    IsoGrid *grid;

    float chock_time;
};

