#pragma once

#include <set>
#include <list>

#include "Tree/Graphics.hpp"
#include "Tree/Vec2D.hpp"
#include "Tree/Timer.hpp"

#include "IsoGrid.hpp"

struct Charge {
    Charge( Vec2i pt, Vec2i d ) : point( pt ), dir( d )
    {
        t.Start();
    }

    Vec2i point;
    Vec2i dir;
    Tree::Timer t;
};

class Path {
public:
    Path( IsoGrid *const grid );

    typedef std::set<Vec2i> Points;
    Points points;

    bool Has( Vec2i point );

    void Add( Vec2i point );
    void Add( int x, int y ) { Add( Vec2i( x, y ) ); }

    void Remove( Vec2i point );
    void Remove( int x, int y ) { Remove( Vec2i( x, y ) ); }

    Points Neighbours( Vec2i point );

    bool Chock( Vec2i point, Vec2i dir = Vec2i::zero );

    void Update( float dt );

    void Draw( int x_off, int y_off );
private:
    typedef std::list<Charge> Charges;
    Charges charges;

    sf::Sprite spr;
    sf::Sprite charge;

    IsoGrid *grid;

    float chock_time;

    sf::Sound snd;
};

