#include "Tree/Butler.hpp"

using Tree::Butler;

Butler::Butler()
{

}
Butler::~Butler()
{

}

void Butler::LoadSprites( std::string lua_file )
{
    spr_loader.Load( lua_file );
}

Tree::FntPtr Butler::GetFont( std::string path,
    unsigned int size ) throw( Error::file_not_found )
{
    typedef std::pair<FontMap::iterator, FontMap::iterator> ItPair;

    //find all fonts with the same font file
    ItPair ret = font_map.equal_range( path );
    if( ret.first != ret.second ) {

        //search for the same font size
        //it's important because otherwise they'll get blurry and ugly
        for( FontMap::iterator it = ret.first; it != ret.second; ++it ) {
            if( it->second->GetCharacterSize() == size ) {
                return it->second;
            }
        }
    }
    FntPtr fnt( new sf::Font() );

    if( !fnt->LoadFromFile( path.c_str(), size ) ) {
        std::string s = "Unable to load font: '" + path + "'";
        throw( Error::file_not_found( s.c_str() ) );
    }

    font_map.insert( std::make_pair( path, fnt ) );
    return fnt;
}

Tree::ImgPtr Butler::GetImage( std::string path )
    throw( Error::file_not_found )
{
    ImageMap::iterator it = image_map.find( path );
    if( it != image_map.end() ) {
        return it->second;
    }
    else {
        ImgPtr img( new sf::Image() );

        if( !img->LoadFromFile( path.c_str() ) ) {
            std::string s = "Unable to load image: '" + path + "'";
            throw( Error::file_not_found( s.c_str() ) );
        }

        image_map.insert( std::make_pair( path, img ) );
        return img;
    }
}

Tree::SpritePtr Butler::GetSprite( std::string name )
{
    return spr_loader.Get( name );
}
Tree::Sprites Butler::GetSprites()
{
    return spr_loader.GetSprites();
}
Tree::Sprites Butler::GetSpritesFromFile( std::string file )
{
    return spr_loader.GetSpritesFromFile( file );
}
Tree::Strings Butler::GetSpriteNames()
{
    return spr_loader.GetSpriteNames();
}

