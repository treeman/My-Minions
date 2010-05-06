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

TexObj Butler::GetTex( std::string path )
{
    TexMap::iterator it = tex_map.find( path );
    if( it != tex_map.end() ) {
        return it->second;
    }
    else {
        TexObj tex( path );
        tex_map.insert( std::make_pair( path, tex ) );
        return tex;
    }
}

