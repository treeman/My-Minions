#pragma once

#include <string>
#include <map>

#include "Hge/Hge.hpp"
#include "Tree/Singleton.hpp"

namespace Tree
{
    class Butler : public Singleton<Butler> {
    public:
        Butler();
        ~Butler();

        boost::shared_ptr<hgeFont> GetFont( std::string path );
    private:
        typedef std::map<std::string, boost::shared_ptr<hgeFont> > FontMap;
        FontMap font_map;
    };
}

