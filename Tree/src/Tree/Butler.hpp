#pragma once

#include <string>
#include <map>

#include "Hge/Hge.hpp"
#include "Tree/Singleton.hpp"
#include "Tree/Sprite.hpp"

#define BUTLER Tree::Butler::Instance()

namespace Tree
{
    class Butler : public Singleton<Butler> {
    public:
        Butler();
        ~Butler();

        void LoadSprites( std::string lua_file );

        boost::shared_ptr<hgeFont> GetFont( std::string path );
        TexObj GetTex( std::string path );
        boost::shared_ptr<Sprite> GetSprite( std::string name );
    private:
        typedef std::map<std::string, boost::shared_ptr<hgeFont> > FontMap;
        FontMap font_map;

        typedef std::map<std::string, TexObj> TexMap;
        TexMap tex_map;

        SpriteLoader spr_loader;
    };
}

