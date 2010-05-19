#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Lua/Lua.hpp"
#include "Tree/Errorhandling.hpp"

namespace Tree
{
    class SimpleSprite {
    public:
        SimpleSprite() : color( 0 ), x_off( 0 ), y_off ( 0 ), is_anim( false )
        { }

        boost::shared_ptr<hgeSprite> spr;
        DWORD color;
        TexObj tex;
        float x_off, y_off;
        bool is_anim;
    };

    class Sprite {
    public:
        void Update( float dt );

        void Render( float x, float y );
        void RenderEx( float x, float y, float rot,
            float hscale = 1.0f, float vscale = 0.0f );
    private:
        Sprite();

        friend class SpriteLoader;

        typedef std::vector<boost::shared_ptr<SimpleSprite> > Sprites;

        Sprites sprites;
    };

    class SpriteLoader {
    public:
        SpriteLoader();

        void Load( std::string lua_file ) throw( Error::lua_error & );

        boost::shared_ptr<Sprite> Get( std::string name );
    private:
        typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
        SpriteMap sprite_map;

        //lua helper to load a sprite
        bool LoadSprite( lua_State *L, boost::shared_ptr<Sprite> spr );
    };
}

