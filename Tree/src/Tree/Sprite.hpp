#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Lua/Lua.hpp"
#include "Tree/Errorhandling.hpp"
#include "Tree/Graphics.hpp"
#include "Tree/Util.hpp"

namespace Tree
{
    class SimpleSprite {
    public:
        SimpleSprite() : x_off( 0 ), y_off ( 0 )
        { }

        sf::Sprite spr;
        float x_off, y_off;
    };

    //meta info about the sprite
    struct SpriteInfo {
        std::string file_loaded_from;
        std::string name;
    };

    class Sprite : public sf::Drawable {
    public:
        SpriteInfo Info() const;

        void Draw();
    private:
        Sprite();
        friend class SpriteLoader;

        void Render( sf::RenderTarget &target ) const;

        typedef boost::shared_ptr<SimpleSprite> SimplePtr;
        typedef std::vector<SimplePtr> Sprites;

        Sprites sprites;

        SpriteInfo info;
    };

    typedef boost::shared_ptr<Sprite> SpritePtr;
    typedef std::vector<SpritePtr> Sprites;
    typedef std::map<std::string, SpritePtr> SpriteMap;

    class SpriteLoader {
    public:
        SpriteLoader();

        //different ways to load a file, either load it once or force a load
        //even if loaded before
        void Load( std::string lua_file ) throw( Error::lua_error & );
        void ForceLoad( std::string lua_file ) throw( Error::lua_error & );

        SpritePtr Get( std::string name );

        //so we can comb through all sprites we've loaded so far
        Sprites GetSprites();
        Sprites GetSpritesFromFile( std::string file );
        Strings GetSpriteNames();
    private:
        SpriteMap sprite_map;
        Strings parsed_files;

        //lua helper to load a sprite
        bool LoadSprite( lua_State *L, SpritePtr spr );
    };
}

