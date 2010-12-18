#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>

#include "Tree/Singleton.hpp"
#include "Tree/Errorhandling.hpp"
#include "Tree/Sprite.hpp"
#include "Tree/Util.hpp"

namespace Tree
{
    typedef boost::shared_ptr<sf::Font> FntPtr;
    typedef boost::shared_ptr<sf::Image> ImgPtr;

    class Butler {
    public:
        Butler();
        ~Butler();

        void LoadSprites( std::string lua_file );

        FntPtr GetFont( std::string path, unsigned int size = 30 ) throw( Error::file_not_found );
        ImgPtr GetImage( std::string path ) throw( Error::file_not_found );

        Tree::SpritePtr GetSprite( std::string name );
        Tree::Sprites GetSprites();
        Tree::Sprites GetSpritesFromFile( std::string file );
        Tree::Strings GetSpriteNames();
    private:
        typedef std::multimap<std::string, FntPtr> FontMap;
        FontMap font_map;

        typedef std::map<std::string, ImgPtr> ImageMap;
        ImageMap image_map;

        SpriteLoader spr_loader;
    };
}

