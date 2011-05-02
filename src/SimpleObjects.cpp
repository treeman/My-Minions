#include <sstream>

#include "Tree/Log.hpp"
#include "SimpleObjects.hpp"

SilencerObject::SilencerObject()
{
    spr = BUTLER->CreateSprite( "gfx/deleter.png" );
}

void SilencerObject::ChargeIn( Charge &charge )
{
    charge.can_kill = true;
}

MusicObject::MusicObject( std::string spr_path, std::string snd_path )
{
    spr = BUTLER->CreateSprite( spr_path );
    snd = BUTLER->CreateSound( snd_path );
}

void MusicObject::ChargeIn( Charge &charge )
{
    if( charge.type ) { snd.Play(); }
}

NotObject::NotObject()
{
    spr = BUTLER->CreateSprite( "gfx/not.png" );
}

void NotObject::ChargeIn( Charge &charge )
{
    charge.type = !charge.type;
}

AndObject::AndObject()
{
    Reset();

    spr = BUTLER->CreateSprite( "gfx/and.png" );
}

void AndObject::ChargeIn( Charge &charge )
{
    ++n;
    if( n > 1 ) {
        status = status && charge.type;
    }
    else {
        status = charge.type;
    }

    if( n >= 2 ) {
        Charge res;
        res.type = status;
        QueueCharge( res );
    }

    charge.can_kill = true;

    //std::stringstream ss;
    //ss << "And's status: " << status << " " << n <<" "<< HasOutCharge();
    //Tree::VisualDebug( "and", ss.str() );
}

void AndObject::ChargeOutSent() { Reset(); }

void AndObject::ClockPulse() { Reset(); }

void AndObject::Reset()
{
    n = status = 0;
}

OrObject::OrObject()
{
    Reset();

    spr = BUTLER->CreateSprite( "gfx/or.png" );
}

void OrObject::ChargeIn( Charge &charge )
{
    ++n;
    if( n > 1 ) {
        status = status || charge.type;
    }
    else {
        status = charge.type;
    }

    if( n >= 2 ) {
        Charge res;
        res.type = status;
        QueueCharge( res );
    }

    charge.can_kill = true;

    //std::stringstream ss;
    //ss << "And's status: " << status << " " << n <<" "<< HasOutCharge();
    //Tree::VisualDebug( "and", ss.str() );
}

void OrObject::ChargeOutSent() { Reset(); }

void OrObject::ClockPulse() { Reset(); }

void OrObject::Reset()
{
    n = status = 0;
}

