#include "Tree/Butler.hpp"
#include "Tree/Log.hpp"
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

    right_dir.SetPosition( pos );
    left_dir.SetPosition( pos );
    up_dir.SetPosition( pos );
    down_dir.SetPosition( pos );
}
void PathObject::Render()
{
    Tree::Draw( spr );
    if( ShowDirection() ) {
        if( face == Vec2i::right ) Tree::Draw( right_dir );
        else if( face == Vec2i::down ) Tree::Draw( down_dir );
        else if( face == Vec2i::left ) Tree::Draw( left_dir );
        else if( face == Vec2i::up ) Tree::Draw( up_dir );
    }
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

    right_dir = BUTLER->CreateSprite( "gfx/right_dir.png" );
    left_dir = BUTLER->CreateSprite( "gfx/left_dir.png" );
    up_dir = BUTLER->CreateSprite( "gfx/up_dir.png" );
    down_dir = BUTLER->CreateSprite( "gfx/down_dir.png" );
}

