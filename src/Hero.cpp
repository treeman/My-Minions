#include "Tree/Butler.hpp"
#include "Hero.hpp"

Hero::Hero()
{
    spr = BUTLER->CreateSprite( "hero" );
}

void Hero::Update( float dt )
{
    UpdateMovement( dt );
}

void Hero::NewPos( Vec2i pos )
{
    spr.SetPosition( pos );
}

void Hero::Render()
{
    Tree::Draw( spr );
}

