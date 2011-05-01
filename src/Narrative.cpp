#include "Tree/Butler.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Log.hpp"

#include "Narrative.hpp"


Msg::Msg( std::string s, float time, float fade, float solid ) :
    timestamp( time ), fade_time( fade ), solid_time( solid )
{
    str = BUTLER->CreateString( "fnt/arial.ttf", 15 );
    str.SetText( s );
}

bool Msg::operator < ( const Msg &o )
{
    return TimeToStart() < o.TimeToStart();
}

float Msg::GetWidth()
{
    return str.GetRect().GetWidth();
}

void Msg::Start()
{
    t.Start();
}
bool Msg::IsVisible()
{
    return !t.IsStarted() || t.GetTime() > fade_time + solid_time;
}

void Msg::Draw( Vec2i pos )
{
    if( IsVisible() ) {
        str.SetPosition( pos.x, pos.y );
        sf::Color color = Tree::Color( 0xffffffff );
        const float time = t.GetTime() - solid_time;
        L_ << time << '\n';
        if( time > 0 ) {
            color.a = 255 * (1.0 - time / fade_time);
        }

        Tree::Draw( str );
    }
}

Narrative::Narrative()
{
    msgs.push_back( Msg( "It's Dangerous to go Alone!", 0, 1, 0 ) );
    msgs.push_back( Msg( "Take This!", 1, 1, 1 ) );
    msgs.push_back( Msg( "It's a scooby do?", 3, 4, 3 ) );

    is_done = false;

    msgs.sort();
}

void Narrative::Start()
{
    t.Restart();
}
void Narrative::Stop()
{
    t.Stop();
}
void Narrative::Pause()
{
    t.Pause();
}
void Narrative::Skip()
{

}

bool Narrative::IsDone()
{
    return is_done;
}

void Narrative::Update( float dt )
{
    const float time = t.GetTime();
    std::stringstream s;
    s << "time: " << time;
    Tree::VisualDebug( s.str() );

    if( time > curr_msgs.front().TimeToStart() ) {
        if( !msgs.empty() ) {
            Msg new_msg = msgs.front();
            msgs.pop_front();
            //new_msg.Start();
            curr_msgs.push_front( new_msg );
            t.Restart();
        }
        else {
            is_done = true;
        }
    }
}

void Narrative::Draw()
{
    const int line_h = 20;
    int n = 0;
    for( Msgs::iterator it = curr_msgs.begin(); it != curr_msgs.end(); ++it ) {
        const int w = it->GetWidth();
        const Vec2i pos(
            Tree::GetWindowWidth() / 2 - w / 2,
            Tree::GetWindowHeight() - 30 - line_h * ( 2 - n )
        );

        it->Draw( pos );
        ++n;

        if( n > 1 ) return;
    }
}

