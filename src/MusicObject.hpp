#pragma once

#include "Tree/Butler.hpp"
#include "PathObject.hpp"

class MusicObject : public PathObject {
public:
    MusicObject( std::string spr, std::string snd );

    Charge ChargeIn( Charge &charge );
private:
    void NewPos( Vec2i pos );
    void Render();

    sf::Sprite spr;
    sf::Sound snd;
};

