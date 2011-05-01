#include <sstream>

#include "Tree/Tweaks.hpp"
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
            o.reset( new MusicObject( "gfx/music1.png",
                TWEAKS->GetString( "thud1" )));
            break;
        case 1:
            o.reset( new MusicObject( "gfx/music2.png",
                TWEAKS->GetString( "thud2" )));
            break;
        case 2:
            o.reset( new MusicObject( "gfx/music3.png",
                TWEAKS->GetString( "tick" )));
            break;
        case 3:
            o.reset( new MusicObject( "gfx/music4.png",
                TWEAKS->GetString( "spike" )));
            break;
        case 4:
            o.reset( new MusicObject( "gfx/music5.png",
                TWEAKS->GetString( "blip" )));
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
            o.reset( new OrObject() );
            break;
    }
    o->SetObjNum( num );
    return o;
}

