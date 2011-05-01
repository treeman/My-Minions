#pragma once

#include <set>
#include <list>

#include "Tree/Graphics.hpp"
#include "Tree/Vec2D.hpp"
#include "Tree/Timer.hpp"

#include "IsoGrid.hpp"

struct Charge {
    Charge( Vec2i pt, Vec2i d ) : point( pt ), dir( d ), type( 1 )
    { }

    Vec2i point;
    Vec2i dir;

    int type;
};

class Path {
public:
    Path( IsoGrid *const grid );

    void Start();
    void Pause();

    typedef std::set<Vec2i> Points;
    Points points;

    bool Has( Vec2i point );

    void Add( Vec2i point );
    void Add( int x, int y ) { Add( Vec2i( x, y ) ); }

    void Remove( Vec2i point );
    void Remove( int x, int y ) { Remove( Vec2i( x, y ) ); }

    Points Neighbours( Vec2i point );

    bool CanChock( Vec2i point );
    void Chock( Vec2i point, Vec2i dir = Vec2i::zero );

    void Update( float dt );

    void Draw( int x_off, int y_off );
private:
    typedef std::list<Charge> Charges;
    Charges charges;
    Charges chocks;

    void AddChock( Charges &charges, Vec2i point, Vec2i dir );

    sf::Sprite spr;
    sf::Sprite charge;

    IsoGrid *grid;

    float chock_time;
    Tree::Timer t;

    sf::Sound charge_it;
    sf::Sound dead_end;
    sf::Sound split;
    sf::Sound turn;

    bool play_charge;
    bool play_dead_end;
    bool play_split;
    bool play_turn;
};

