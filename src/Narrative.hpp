#pragma once

#include <list>
#include <vector>

#include "Tree/Timer.hpp"
#include "Tree/Graphics.hpp"
#include "Tree/Util.hpp"

struct Msg {
    std::string str;
    Tree::Timer t;
};

class Narrative {
public:
    Narrative();

    bool IsDone();

    void Update( float dt );
    void Draw();
private:
    Tree::Timer t;

    void Add( std::string str );
    typedef std::list<Msg> Msgs;
    Msgs msgs;

    bool is_done;

    sf::String str;
    float offset;
};

