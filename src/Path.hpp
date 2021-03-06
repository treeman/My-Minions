#pragma once

#include <set>
#include <list>
#include <fstream>

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

    bool Has( Vec2i point );
    bool HasObj( Vec2i point );
    bool IsCharged( Vec2i point );
    bool IsChocked( Vec2i point );

    void Rotate( Vec2i point );

    void KillCharges();

    PathObjPtr GetObj( Vec2i point );

    void Add( Vec2i point );
    void Add( int x, int y ) { Add( Vec2i( x, y ) ); }

    void Add( PathObjPtr obj );

    void Remove( Vec2i point );
    void Remove( int x, int y ) { Remove( Vec2i( x, y ) ); }

    bool CanChock( Vec2i point );
    void Chock( Vec2i point, Vec2i dir = Vec2i::zero );

    void Update( float dt );
    void Draw( int x_off, int y_off );

    void Save( std::fstream &file );
    void Load( std::ifstream &file );
private:
    typedef std::set<Vec2i> Points;
    Points points;

    typedef std::list<Charge> Charges;
    Charges charges;
    Charges chocks;

    void AddChock( Charges &charges, Vec2i point, Vec2i dir, int type );
    void AddChock( Charges &charges, Charge chock );

    typedef std::list<PathObjPtr> Objects;
    Objects objects;

    sf::Sprite spr;

    sf::Sprite pos_charge;
    sf::Sprite neg_charge;

    IsoGrid *grid;

    float clock_time;
    Tree::Timer t;

    //sf::Sound charge_it;
    sf::Sound dead_end;
    sf::Sound split;
    sf::Sound turn;

    sf::String fnt;
};

