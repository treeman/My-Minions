#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Lua/Lua.hpp"
#include "Tree/Errorhandling.hpp"

namespace Tree
{
    class BaseSimpleSprite {
    public:
        BaseSimpleSprite() : color( 0xffffffff ), x_off( 0 ), y_off ( 0 )
        { }
        virtual ~BaseSimpleSprite() { }

        virtual void Update( float ) { }
        virtual void Render( float x, float y ) = 0;

        DWORD color;
        TexObj tex;
        float x_off, y_off;
    };

    class SimpleSprite : public BaseSimpleSprite {
    public:
        void Render( float x, float y );

        boost::shared_ptr<hgeSprite> spr;
    };

    class SimpleAnimation : public BaseSimpleSprite {
    public:
        void Update( float dt ) { spr->Update( dt ); }
        void Render( float x, float y );

        boost::shared_ptr<hgeAnimation> spr;
    };

    class Sprite {
    public:
        void Update( float dt );
        void Render( float x, float y );
    private:
        Sprite();

        friend class SpriteLoader;

        typedef std::vector<boost::shared_ptr<BaseSimpleSprite> > Sprites;

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

