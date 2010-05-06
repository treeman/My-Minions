#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Hge/Hge.hpp"
#include "Lua/Lua.hpp"
#include "Tree/Errorhandling.hpp"

//Shall become a helper for managing tex and sprites
//Should be able to load sprites and animes from lua
namespace Tree
{
    struct Sprite {
        Sprite( std::string file, float x, float y, float w, float h, DWORD color = 0 );

        TexObj tex;
        boost::shared_ptr<hgeSprite> spr;
        DWORD color;
    };

    /*struct SimpleSprite {
        boost::shared_ptr<hgeSprite> spr;
        DWORD color;
        TexObj tex;
        float x_off, y_off;
    };

    struct SimpleAnimation {
        boost::shared_ptr<hgeAnimation> spr;
        DWORD color;
        TexObj tex;
        float x_off, y_off;
    };

    class Sprite {
    public:

    void Update( float dt );
    void Render( float x, float y );
    private:
        friend class SpriteLoader;

        typedef std::vector<SimpleSprite> Sprites;
        typedef std::vector<SimpleAnimation> Anims;

        Sprites sprites;
        Anims anims;
    };*/

    class SpriteLoader {
    public:
        SpriteLoader();

        void Load( std::string lua_file ) throw( Error::lua_error & );

        boost::shared_ptr<Sprite> Get( std::string name );
    private:
        typedef std::map<std::string, boost::shared_ptr<Sprite> > SpriteMap;
        SpriteMap sprite_map;
    };
}

