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
    unsigned int size ) throw( Error::resource_not_found )
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
        throw( Error::resource_not_found( "Unable to load font: '" + path + "'" ) );
    }

    font_map.insert( std::make_pair( path, fnt ) );
    return fnt;
}

Tree::ImgPtr Butler::GetImage( std::string path, bool shall_smooth )
    throw( Error::resource_not_found )
{
    ImageMap::iterator it = image_map.find( path );
    if( it != image_map.end() ) {
        return it->second;
    }
    else {
        ImgPtr img( new sf::Image() );

        if( !img->LoadFromFile( path.c_str() ) ) {
            throw( Error::resource_not_found(
                "Unable to load image: '" + path + "'" ) );
        }
        img->SetSmooth( shall_smooth );

        image_map.insert( std::make_pair( path, img ) );
        return img;
    }
}

Tree::SndPtr Butler::GetSoundBuffer( std::string path )
    throw( Error::resource_not_found )
{
    SoundMap::iterator it = sound_map.find( path );
    if( it != sound_map.end() ) {
        return it->second;
    }
    else {
        SndPtr snd( new sf::SoundBuffer() );

        if( !snd->LoadFromFile( path.c_str() ) ) {
            throw( Error::resource_not_found(
                "Unable to load sound: '" + path + "'" ) );
        }

        sound_map.insert( std::make_pair( path, snd ) );
        return snd;
    }
}

sf::Sprite Butler::CreateSprite( std::string name )
    throw( Error::resource_not_found )
{
    if( spr_loader.HasCustomSprite( name ) ) {
        return spr_loader.Create( name );
    }
    else {
        try {
            sf::Sprite spr;
            spr.SetImage( *GetImage( name ) );
            return spr;
        }
        catch( Error::resource_not_found & ) {
            throw( Error::resource_not_found(
                "Unable to load sprite: '" + name + "'" ) );
        }
    }
}

sf::String Butler::CreateString( std::string fnt_path, int size )
    throw( Error::resource_not_found )
{
    sf::String str;
    str.SetFont( *GetFont( fnt_path, size ) );
    str.SetSize( size );
    return str;
}

sf::Sound Butler::CreateSound( std::string path )
    throw( Error::resource_not_found )
{
    sf::Sound snd;
    snd.SetBuffer( *GetSoundBuffer( path ) );
    return snd;
}

