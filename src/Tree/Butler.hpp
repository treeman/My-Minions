#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Tree/Singleton.hpp"
#include "Tree/Errorhandling.hpp"
#include "Tree/Sprite.hpp"
#include "Tree/Util.hpp"

namespace Tree
{
    typedef boost::shared_ptr<sf::Font> FntPtr;
    typedef boost::shared_ptr<sf::Image> ImgPtr;
    typedef boost::shared_ptr<sf::SoundBuffer> SndPtr;

    class Butler {
    public:
        Butler();
        ~Butler();

        void LoadSprites( std::string lua_file );

        FntPtr GetFont( std::string path, unsigned int size = 30 )
            throw( Error::resource_not_found );
        ImgPtr GetImage( std::string path, bool shall_smooth = false )
            throw( Error::resource_not_found );
        SndPtr GetSoundBuffer( std::string path )
            throw( Error::resource_not_found );

        sf::Sprite CreateSprite( std::string name )
            throw( Error::resource_not_found );
        sf::String CreateString( std::string fnt_path, int size )
            throw( Error::resource_not_found );
        sf::Sound CreateSound( std::string snd_path )
            throw( Error::resource_not_found );
    private:
        typedef std::multimap<std::string, FntPtr> FontMap;
        FontMap font_map;

        typedef std::map<std::string, ImgPtr> ImageMap;
        ImageMap image_map;

        SpriteLoader spr_loader;

        typedef std::map<std::string, SndPtr> SoundMap;
        SoundMap sound_map;
    };
}

