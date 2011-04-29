#pragma once

#include <SFML/Graphics.hpp>

#include "Tree/Rect.hpp"

namespace Tree
{
    void Draw( const sf::Drawable &obj );

    bool IsVisible( const Tree::Rect &r );

    //mostly for lazy drawing
    void Redraw();
    void Redraw( const Tree::Rect &rect );
    void ClearWindow( sf::Color col = sf::Color() );
    bool NeedRedraw();

    void DrawLazy();
    void DrawNonLazy();
    bool DrawingLazy();

    //create an sfml color from a hex value eg 0xff00ffff
    //with a r g b as the parts
    extern sf::Color Color( unsigned long hex_color );
}

