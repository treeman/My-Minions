#include "Tree/Butler.hpp"

using Tree::Butler;

Butler::Butler()
{

}
Butler::~Butler()
{

}

boost::shared_ptr<hgeFont> Butler::GetFont( std::string path )
{
    FontMap::iterator it = font_map.find( path );
    if( it != font_map.end() ) {
        return it->second;
    }
    else {
        boost::shared_ptr<hgeFont> fnt( new hgeFont( path.c_str() ) );
        font_map.insert( std::make_pair( path, fnt ) );
        return fnt;
    }
}

