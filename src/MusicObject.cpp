#include "Tree/Butler.hpp"

#include "MusicObject.hpp"

MusicObject::MusicObject( std::string spr_path, std::string snd_path )
{
    spr = BUTLER->CreateSprite( spr_path );
    snd = BUTLER->CreateSound( snd_path );
}


Charge MusicObject::ChargeIn( Charge &charge )
{
    if( charge.type ) {
        snd.Play();
    }
    return charge;
}

void MusicObject::NewPos( Vec2i pos )
{
    spr.SetPosition( pos );
}

void MusicObject::Render()
{
    Tree::Draw( spr );
}

