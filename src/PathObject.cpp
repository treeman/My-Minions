#include "PathObject.hpp"

PathObject::PathObject()
{
    Reset();
}

PathObject::PathObject( sf::Sprite _spr ) : spr( _spr )
{
    Reset();
}

void PathObject::NewPos( Vec2i pos )
{
    spr.SetPosition( pos );
}
void PathObject::Render()
{
    Tree::Draw( spr );
}

Charge PathObject::ChargeOut()
{
    has_charge = false;
    ChargeOutSent();
    return out_charge;
}

void PathObject::Rotate()
{
    if( face == Vec2i::right ) face = Vec2i::down;
    else if( face == Vec2i::down ) face = Vec2i::left;
    else if( face == Vec2i::left ) face = Vec2i::up;
    else if( face == Vec2i::up ) face = Vec2i::right;
}

Vec2i PathObject::Facing()
{
    return face;
}

void PathObject::QueueCharge( Charge &charge )
{
    has_charge = true;
    out_charge = charge;
    out_charge.dir = face;
}

void PathObject::Reset()
{
    has_charge = false;
    face = Vec2i::right;
}

