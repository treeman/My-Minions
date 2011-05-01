#pragma once

#include <set>
#include <list>

#include "Tree/Graphics.hpp"
#include "Tree/Vec2D.hpp"
#include "Tree/Timer.hpp"

#include "IsoGrid.hpp"
#include "Charge.hpp"
#include "PathObject.hpp"

class Path {
public:
    Path( IsoGrid *const grid );

    void Start();
    void Pause();

    void SetClockTime( float clock_time );

    typedef std::set<Vec2i> Points;

    bool Has( Vec2i point );
    bool HasObj( Vec2i point );
    PathObjPtr GetObj( Vec2i point );

    void Add( Vec2i point );
    void Add( int x, int y ) { Add( Vec2i( x, y ) ); }

    void Add( PathObjPtr obj );

    void Remove( Vec2i point );
    void Remove( int x, int y ) { Remove( Vec2i( x, y ) ); }

    Points Neighbours( Vec2i point );

    bool CanChock( Vec2i point );
    void Chock( Vec2i point, Vec2i dir = Vec2i::zero );

    void Update( float dt );

    void Draw( int x_off, int y_off );
private:
    Points points;

    typedef std::list<Charge> Charges;
    Charges charges;
    Charges chocks;

    void AddChock( Charges &charges, Vec2i point, Vec2i dir );

    typedef std::list<PathObjPtr> Objects;
    Objects objects;

    sf::Sprite spr;
    sf::Sprite charge;

    IsoGrid *grid;

    float clock_time;
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

