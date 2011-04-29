#include "Tree/Graphics.hpp"
#include "Tree/Game.hpp"

void Tree::Draw( const sf::Drawable &obj )
{
    GAME->Draw( obj );
}

bool Tree::IsVisible( const Tree::Rect &r )
{
    return r.x2 > 0 && r.y2 > 0;
        //&& r.x1 < Tree::GetWindowWidth()
        //&& r.y1 < Tree::GetWindowHeight();
    return false;
}

void Tree::Redraw()
{
    Tree::ClearWindow();
}
void Tree::Redraw( const Tree::Rect &rect )
{
    GAME->PortionRedrawn( rect );
}

void Tree::ClearWindow( sf::Color col )
{
    GAME->ClearWindow( col );
}
bool Tree::NeedRedraw()
{
    return GAME->NeedRedraw();
}

void Tree::DrawLazy()
{
    GAME->DrawLazy();
}
void Tree::DrawNonLazy()
{
    GAME->DrawNormal();
}
bool Tree::DrawingLazy()
{
    return GAME->DrawingLazy();
}

sf::Color Tree::Color( unsigned long hex_color )
{
    int a = hex_color >> 24;
    int r = (hex_color >> 16) & 0xFF;
    int g = (hex_color >> 8) & 0xFF;
    int b = hex_color & 0xFF;
    return sf::Color( r, g, b, a );
}

