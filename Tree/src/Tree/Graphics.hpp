#pragma once

#include <SFML/Graphics.hpp>

namespace Tree
{
    void Draw( const sf::Drawable &obj );

    //create an sfml color from a hex value eg 0xff00ffff
    //with a r g b as the parts
    extern sf::Color Color( unsigned long hex_color );
}

