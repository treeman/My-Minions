#include "Tree/Tweaks.hpp"
#include "Tree/Log.hpp";

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
        L_ << "Imma move now kk?";
        origin = pos;
        destination = next_pos;
    }
}

void MoveableObject::UpdateMovement( float dt )
{
    if( IsMoving() ) {
        const Vec2f movement = Vec2f( move_dir.x * move_speed,
                                      move_dir.y * move_speed );

        const Vec2f next_pos = pos + movement;
        pos = next_pos;
    }
}

void MoveableObject::Init()
{
    //origin = destination = pos;
    in_movement = false;
    move_speed = TWEAKS->GetNum( "hero_move_speed" );
}

