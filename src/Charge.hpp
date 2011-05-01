#pragma once

#include "Tree/Vec2D.hpp"

struct Charge {
    Charge( Vec2i pt, Vec2i d ) : point( pt ), dir( d ), type( 1 )
    { }

    Vec2i point;
    Vec2i dir;

    int type;
};

