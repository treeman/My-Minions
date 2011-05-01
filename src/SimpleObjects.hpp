#pragma once

#include "Tree/Butler.hpp"
#include "PathObject.hpp"

class SilencerObject : public PathObject {
public:
    SilencerObject();

    void ChargeIn( Charge &charge );
};

class MusicObject : public PathObject {
public:
    MusicObject( std::string spr, std::string snd );

    void ChargeIn( Charge &charge );
private:
    sf::Sound snd;
};

class NotObject : public PathObject {
public:
    NotObject();

    void ChargeIn( Charge &charge );
};

class AndObject : public PathObject {
public:
    AndObject();

    void ChargeIn( Charge &charge );
    void ChargeOutSent();

    void ClockPulse();
private:
    void Reset();

    int n;
    bool status;
};

class OrObject : public PathObject {
public:
    OrObject();

    void ChargeIn( Charge &charge );
    void ChargeOutSent();

    void ClockPulse();
private:
    void Reset();

    int n;
    bool status;
};

