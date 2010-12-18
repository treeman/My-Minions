#include "Tree/Graphics.hpp"
#include "Tree/Game.hpp"

void Tree::Draw( const sf::Drawable &obj )
{
    Tree::Game::Instance()->Draw( obj );
}

sf::Color Tree::Color( unsigned long hex_color )
{
    int a = hex_color >> 24;
    int r = (hex_color >> 16) & 0xFF;
    int g = (hex_color >> 8) & 0xFF;
    int b = hex_color & 0xFF;
    return sf::Color( r, g, b, a );
}

