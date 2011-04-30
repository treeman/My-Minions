#include "Tree/Butler.hpp"
#include "Tile.hpp"

Tile::Tile( sf::Sprite base_spr, Vec2i _pos, int width, int height, Vec2i gpos ) :
    VisualObject( _pos ),
    base( base_spr ), w( width ), h( height ), grid_pos( gpos )
{
    highlight = BUTLER->CreateSprite( "gfx/tile_overlay.png" );
}

Vec2i Tile::GetGridPos()
{
    return grid_pos;
}

void Tile::Update( float dt )
{

}

void Tile::NewPos( Vec2i pos )
{
    base.SetPosition( pos );
    highlight.SetPosition( pos );
}

void Tile::Render()
{
    Tree::Draw( base );
    //Tree::Draw( highlight );
}

