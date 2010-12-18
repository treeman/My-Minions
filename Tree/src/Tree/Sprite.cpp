#include "Sprite.hpp"
#include "Tree/Log.hpp"
#include "Tree/Butler.hpp"

#include <boost/foreach.hpp>

using Tree::SimpleSprite;
using Tree::SpriteInfo;
using Tree::Sprite;
using Tree::SpriteLoader;

Sprite::Sprite()
{

}

SpriteInfo Sprite::Info() const
{
    return info;
}

void Sprite::Draw()
{
    BOOST_FOREACH( SimplePtr s, sprites ) {
        Tree::Draw( s->spr );
    }
}

void Sprite::Render( sf::RenderTarget &target ) const
{
    BOOST_FOREACH( SimplePtr s, sprites ) {
        target.Draw( s->spr );
    }
}

SpriteLoader::SpriteLoader() { }

void SpriteLoader::Load( std::string lua_file ) throw( Error::lua_error & )
{
    if( std::find( parsed_files.begin(), parsed_files.end(), lua_file ) != parsed_files.end() ) {
        return;
    }

    ForceLoad( lua_file );

    parsed_files.push_back( lua_file );
}

void SpriteLoader::ForceLoad( std::string lua_file ) throw( Error::lua_error & )
{
    L_ << "loading sprite file '" << lua_file << "'\n";
    LuaState L;

    if( luaL_dofile( L, lua_file.c_str() ) ) {
        const char *str = lua_tostring( L, -1 );
        lua_pop( L, -1 );
        throw( Error::lua_error( str ) );
    }

    lua_getglobal( L, "_G" );
    for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) )
    {
        if( lua_istable( L, -1 ) ) {
            SpritePtr sprite( new Sprite() );

            std::string name = lua_tostring( L, -2 );
            if( !LoadSprite( L, sprite ) ) {

                for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) )
                {
                    LoadSprite( L, sprite );
                }
            }

            if( sprite->sprites.size() )
            {
                SpriteInfo sprite_info;
                sprite_info.file_loaded_from = lua_file;
                sprite_info.name = name;

                sprite->info = sprite_info;
                sprite_map.insert( std::make_pair( name, sprite ) );
            }
        }
    }
}

Tree::SpritePtr SpriteLoader::Get( std::string name )
{
    Tree::SpriteMap::iterator it = sprite_map.find( name );
    if( it == sprite_map.end() ) {
        throw( Error::sprite_not_found( ( "sprite '" + name + "' not found\n" ).c_str() ) );
    }
    else { return it->second; }
}

Tree::Strings SpriteLoader::GetSpriteNames()
{
    Tree::Strings sprites;

    for( Tree::SpriteMap::iterator it = sprite_map.begin(); it != sprite_map.end(); ++it )
    {
        sprites.push_back( it->first );
    }
    return sprites;
}

Tree::Sprites SpriteLoader::GetSprites()
{
    Tree::Sprites sprites;

    for( Tree::SpriteMap::iterator it = sprite_map.begin(); it != sprite_map.end(); ++it )
    {
        sprites.push_back( it->second );
    }
    return sprites;
}

Tree::Sprites SpriteLoader::GetSpritesFromFile( std::string file )
{
    Tree::Sprites sprites;

    for( Tree::SpriteMap::iterator it = sprite_map.begin(); it != sprite_map.end(); ++it )
    {
        if( it->second->Info().file_loaded_from == file ) {
            sprites.push_back( it->second );
        }
    }
    return sprites;
}

bool SpriteLoader::LoadSprite( lua_State *L, SpritePtr spr )
{
    if( lua_istable( L, -1 ) ) {

        std::string path = "";
        float x = 0, y = 0;
        float w = 0, h = 0;
        float x_off = 0, y_off = 0;
        float hot_x = 0;
        float hot_y = 0;
        bool smoothen = false;

        luah::get_num<float>( L, "x", x );
        luah::get_num<float>( L, "y", y );

        luah::get_num<float>( L, "x_off", x_off );
        luah::get_num<float>( L, "y_off", y_off );

        luah::get_num<float>( L, "hotspot_x", hot_x );
        luah::get_num<float>( L, "hotspot_y", hot_y );

        luah::get_bool( L, "smoothen", smoothen );

        if( luah::get_num<float>( L, "w", w ) &&
            luah::get_num<float>( L, "h", h ) &&
            luah::get_string( L, "path", path ) )
        {
            Tree::ImgPtr img = Tree::GetButler()->GetImage( path );

            if( img ) {
                boost::shared_ptr<SimpleSprite> simple( new SimpleSprite() );

                img->SetSmooth( smoothen );
                simple->spr.SetImage( *img );
                simple->spr.SetSubRect( sf::IntRect( x, y, w, h ) );
                simple->spr.SetCenter( hot_x, hot_y );

                simple->x_off = x_off; simple->y_off = y_off;

                spr->sprites.push_back( simple );

                return true;
            }
        }
    }
    return false;
}

