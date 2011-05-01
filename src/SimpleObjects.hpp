#pragma once

#include "Tree/Butler.hpp"
#include "PathObject.hpp"

class SilencerObject : public PathObject {
public:
    SilencerObject();

    Charge ChargeIn( Charge &charge );
};

class MusicObject : public PathObject {
public:
    MusicObject( std::string spr, std::string snd );

    Charge ChargeIn( Charge &charge );
private:
    sf::Sound snd;
};

class NotObject : public PathObject {
public:
    NotObject();

    Charge ChargeIn( Charge &charge );
};

