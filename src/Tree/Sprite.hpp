#pragma once

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "Tree/Lua.hpp"
#include "Tree/Errorhandling.hpp"
#include "Tree/Graphics.hpp"
#include "Tree/Util.hpp"

namespace Tree
{
    class SpriteLoader {
    public:
        SpriteLoader();

        //different ways to load a file, either load it once or force a load
        //even if loaded before
        void Load( std::string lua_file ) throw( Error::lua_error & );
        void ForceLoad( std::string lua_file ) throw( Error::lua_error & );

        bool HasCustomSprite( std::string name );
        sf::Sprite Create( std::string name )
            throw( Error::resource_not_found & );
    private:
        typedef std::map<std::string, sf::Sprite> SpriteMap;
        SpriteMap sprite_map;
        Strings parsed_files;

        //lua helper to load a sprite
        bool LoadSprite( lua_State *L, sf::Sprite *spr ) throw( Error::lua_error & );
    };
}

