#include "Tree/Butler.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Log.hpp"

#include "Narrative.hpp"

const float limit = 1.2;
const float speed = 15.0;

Narrative::Narrative()
{
    str = BUTLER->CreateString( "fnt/arial.ttf", 15 );

    Add( "It's Dangerous to go Alone!" );
    Add( "Here, Take This!" );
    Add( "It's a scooby do?" );
}

bool Narrative::IsDone()
{
    return is_done;
}

void Narrative::Update( float dt )
{
    /*const float time = t.GetTime();
    offset += dt * 20;

    if( time > 5 && msgs.size() ) {
        curr.push_front( msgs.front() );
        //msgs.erase( msgs.begin() );
        msgs.pop_front();
        t.Restart();
    }

    std::stringstream s;
    s << "time: " << time;
    Tree::VisualDebug( s.str() );*/
}

void Narrative::Draw()
{
    const float line_h = 20;

    const int size = msgs.size();
    int n = 0;
    for( Msgs::iterator it = msgs.begin(); it != msgs.end(); ++it, ++n ) {
        const float time_left = n * limit - it->t.GetTime();
        if( time_left < 0 ) {
            str.SetText( it->str );

            const int w = str.GetRect().GetWidth();

            /*if( time_left > -2 ) {
                sf::Color col = Tree::Color( 0xffffffff );
                col.a = 255 * 1 / ( 2 + time_left );
                str.SetColor( col );
            }*/

            Vec2i pos(
                Tree::GetWindowWidth() / 2 - w / 2,
                //Tree::GetWindowHeight() - 30 - line_h * ( 2 - n )
                30 - time_left * speed
            );

            str.SetPosition( pos );

            Tree::Draw( str );
        }
    }
}

void Narrative::Add( std::string str )
{
    Msg msg;
    msg.str = str;
    msg.t.Start();
    msgs.push_back( msg );
}

