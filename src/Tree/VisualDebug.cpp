#include "Tree/Butler.hpp"
#include "Tree/Util.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/Graphics.hpp"
#include "Tree/Log.hpp"

using Tree::Debug;

Debug::Debug() :
    x_pos( Tree::GetWindowWidth() - 5 ),
    y_pos( 7 ),
    line_height( 12 )
{
    render_str = BUTLER->CreateString( "fnt/consola.ttf", 10 );
    render_str.SetColor( Tree::Color( Tree::GetTweaks()->GetNum( "font_debug_color" ) ) );
}

void Debug::Add( std::string s )
{
    temp.push_back( s );
}
void Debug::SetPersistent( std::string id, std::string s )
{
    RemovePersistent( id );
    persistent.insert( std::make_pair( id, s ) );
}
void Debug::RemovePersistent( std::string id )
{
    StringMap::iterator it = persistent.find( id );
    if( it != persistent.end() ) {
        persistent.erase( persistent.find( id ) );
    }
}

void Debug::ResetTempStrings()
{
    temp.clear();
}
void Debug::Render()
{
    int i = 0;
    for( StringMap::iterator it = persistent.begin();
         it != persistent.end(); ++it, ++i )
    {
        render_str.SetText( it->second );
        render_str.SetPosition( x_pos - render_str.GetRect().GetWidth(),
            y_pos + i * line_height );
        Tree::Draw( render_str );
    }

    for( Strings::iterator it = temp.begin();
         it != temp.end(); ++it, ++i )
    {
        render_str.SetText( *it );
        render_str.SetPosition( x_pos - render_str.GetRect().GetWidth(),
            y_pos + i * line_height );
        Tree::Draw( render_str );
    }
}

