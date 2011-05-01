#pragma once

#include <list>

#include "Tree/Timer.hpp"
#include "Tree/Graphics.hpp"
#include "Tree/Util.hpp"

class Msg {
public:
    Msg( std::string msg, float timestamp, float fade_time, float solid_time );

    float TimeToStart() const { return timestamp; }

    bool operator < ( const Msg &o );

    float GetWidth();

    void Start();
    bool IsVisible();

    void Draw( Vec2i pos );
private:
    sf::String str;

    float timestamp;
    float fade_time;
    float solid_time;

    Tree::Timer t;
};

class Narrative {
public:
    Narrative();

    void Start();
    void Stop();
    void Pause();
    void Skip();

    bool IsDone();

    void Update( float dt );
    void Draw();
private:
    Tree::Timer t;

    typedef std::list<Msg> Msgs;
    Msgs msgs;
    Msgs curr_msgs;

    bool is_done;
};

