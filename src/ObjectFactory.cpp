#include <sstream>

#include "ObjectFactory.hpp"
#include "SimpleObjects.hpp"

int NumObjects()
{
    return 9;
}

PathObjPtr GetObject( size_t num ) throw( Error::resource_not_found )
{
    // Hacky but meh :)
    PathObjPtr o;
    switch( num ) {
        case 0:
            o.reset( new MusicObject( "gfx/music1.png", "snd/play.wav" ) );
            break;
        case 1:
            o.reset( new MusicObject( "gfx/music2.png", "snd/blip.wav" ) );
            break;
        case 2:
            o.reset( new MusicObject( "gfx/music3.png", "snd/coin.wav" ) );
            break;
        case 3:
            o.reset( new MusicObject( "gfx/music4.png", "snd/tick.wav" ) );
            break;
        case 4:
            o.reset( new MusicObject( "gfx/music5.png", "snd/twang.wav" ) );
            break;
        case 5:
            o.reset( new SilencerObject() );
            break;
        case 6:
            o.reset( new NotObject() );
            break;
        case 7:
            o.reset( new AndObject() );
            break;
        case 8:
            o.reset( new AndObject() );
            break;
    }
    return o;
}

