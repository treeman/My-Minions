#include "Tree/Log.hpp"
#include "SimpleObjects.hpp"

SilencerObject::SilencerObject()
{
    spr = BUTLER->CreateSprite( "gfx/deleter.png" );
}

Charge SilencerObject::ChargeIn( Charge &charge )
{
    charge.can_kill = true;
    return charge;
}

MusicObject::MusicObject( std::string spr_path, std::string snd_path )
{
    spr = BUTLER->CreateSprite( spr_path );
    snd = BUTLER->CreateSound( snd_path );
}

Charge MusicObject::ChargeIn( Charge &charge )
{
    if( charge.type ) { snd.Play(); }
    return charge;
}

NotObject::NotObject()
{
    spr = BUTLER->CreateSprite( "gfx/not.png" );
}

Charge NotObject::ChargeIn( Charge &charge )
{
    charge.type = !charge.type;
    return charge;
}

