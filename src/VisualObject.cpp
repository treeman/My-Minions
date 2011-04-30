#include "VisualObject.hpp"

VisualObject::VisualObject()
{ }
VisualObject::VisualObject( Vec2i _pos ) :
    pos( _pos )
{
    SetPos( pos );
}

VisualObject::~VisualObject()
{ }

void VisualObject::SetPos( Vec2i _pos )
{
    pos = _pos;
    Redraw();
    NewPos( pos );
}
void VisualObject::SetPos( int x, int y )
{
    SetPos( Vec2i( x, y ) );
}
Vec2i VisualObject::GetPos()
{
    return pos;
}

void VisualObject::Move( int dx, int dy )
{
    SetPos( pos.x + dx, pos.y + dy );
}

