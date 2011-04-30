#include "Tree/Tweaks.hpp"
#include "Tree/Log.hpp"

#include "MoveableObject.hpp"

MoveableObject::MoveableObject()
{
    Init();
}
MoveableObject::MoveableObject( Vec2i pos ) : VisualObject( pos )
{
    Init();
}
MoveableObject::~MoveableObject() { }

bool MoveableObject::IsMoving()
{
    return in_movement;
}

Vec2f MoveableObject::GetDestination()
{
    return destination;
}
Vec2f MoveableObject::GetOrigin()
{
    return origin;
}

void MoveableObject::MoveTowards( Vec2f next_pos )
{
    if( !IsMoving() ) {
        origin = pos;
        destination = next_pos;
        in_movement = true;
    }
}

void MoveableObject::UpdateMovement( float dt )
{
    if( IsMoving() ) {
        //const Vec2f movement = Vec2f( move_dir.x * move_speed,
        //                              move_dir.y * move_speed );
        const Vec2i movement( 10, 10 );

        //const Vec2f next_pos = pos + movement;
        const Vec2i next_pos = (pos + movement) * dt;

        std::stringstream ss;
        ss << "movement: " << movement;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "curr pos: " << pos;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "next_pos: " << next_pos;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        pos = next_pos;
    }
}

void MoveableObject::Init()
{
    //origin = destination = pos;
    in_movement = false;
    move_speed = TWEAKS->GetNum( "hero_move_speed" );
}

