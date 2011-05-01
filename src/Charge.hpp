#pragma once

#include "Tree/Vec2D.hpp"

struct Charge {
    Charge() : can_kill( true ) { }
    Charge( Vec2i pt, Vec2i d, int _type ) :
            point( pt ), dir( d ), type( _type ), can_kill( false )
    { }

    bool operator == ( const Charge &c ) {
        return point == c.point && dir == c.dir;
    }

    Vec2i point;
    Vec2i dir;

    int type;

    bool can_kill;
};

