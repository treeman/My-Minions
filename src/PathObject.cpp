#include "PathObject.hpp"

PathObject::PathObject( sf::Sprite _spr ) : spr( _spr )
{

}

void PathObject::NewPos( Vec2i pos )
{
    spr.SetPosition( pos );
}
void PathObject::Render()
{
    Tree::Draw( spr );
}

