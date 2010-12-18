#include "Tree/Butler.hpp"
#include "Tree/Util.hpp"
#include "Tree/Debug.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/Graphics.hpp"

using Tree::Debug;

Debug::Debug() :
    x_pos( Tree::GetWindowWidth() - 5 ),
    y_pos( 7 ),
    line_height( 12 )
{
    render_str.SetFont( *Tree::GetButler()->GetFont( "fnt/consola.ttf", 10 ) );
    render_str.SetSize( 10 );
    render_str.SetColor( Tree::Color( Tree::GetTweaks()->GetDouble( "font_debug_color" ) ) );
}

void Debug::Add( std::string s )
{
    temp.push_back( s );
}
void Debug::SetPersistent( std::string id, std::string s )
{
    persistent.insert( std::make_pair( id, s ) );
}
void Debug::RemovePersistent( std::string id )
{
    persistent.erase( persistent.find( id ) );
}

void Debug::ResetTempStrings()
{
    temp.clear();
}
void Debug::Draw()
{
    for( unsigned int i = 0; i < temp.size(); ++i ) {
        render_str.SetText( temp[i] );
        render_str.SetPosition( x_pos - render_str.GetRect().GetWidth(),
            y_pos + i * line_height );
        Tree::Draw( render_str );
    }
}

