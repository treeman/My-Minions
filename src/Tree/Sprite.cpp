#include "Sprite.hpp"
#include "Tree/Log.hpp"
#include "Tree/Butler.hpp"

#include <boost/foreach.hpp>

using Tree::SpriteLoader;
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
    Tree::LuaState L;

    if( luaL_dofile( L, lua_file.c_str() ) ) {
        const char *str = lua_tostring( L, -1 );
        lua_pop( L, -1 );
        throw( Error::lua_error( str ) );
    }

    lua_getglobal( L, "_G" );
    for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) )
    {
        if( lua_istable( L, -1 ) ) {
            std::string name = lua_tostring( L, -2 );

            sf::Sprite spr;
            if( LoadSprite( L, &spr ) ) {
                sprite_map.insert( std::make_pair( name, spr ) );
            }
        }
    }
}

bool SpriteLoader::HasCustomSprite( std::string name )
{
    return sprite_map.find( name ) != sprite_map.end();
}

sf::Sprite SpriteLoader::Create( std::string name ) throw( Error::resource_not_found & )
{
    SpriteMap::iterator it = sprite_map.find( name );
    if( it == sprite_map.end() ) {
        throw( Error::resource_not_found( ( "sprite '" + name + "' not found\n" ).c_str() ) );
    }
    else { return it->second; }
}

bool SpriteLoader::LoadSprite( lua_State *L, sf::Sprite *spr ) throw( Error::lua_error & )
{
    if( lua_istable( L, -1 ) ) {
        // Hack to not try to load package.path into our sprite loading
        // But it is trying to load a crapload of other stuff..
        std::string name = lua_tostring( L, -2 );
        if( name == "package" ) return false;
        //L_<< "trying to load " << name << '\n';

        std::string path = "";
        float x = 0, y = 0;
        float w = 0, h = 0;
        float x_off = 0, y_off = 0;
        float hot_x = 0;
        float hot_y = 0;
        bool smoothen = false;

        Tree::get_num<float>( L, "x", x );
        Tree::get_num<float>( L, "y", y );

        Tree::get_num<float>( L, "w", w );
        Tree::get_num<float>( L, "h", h );

        Tree::get_num<float>( L, "x_off", x_off );
        Tree::get_num<float>( L, "y_off", y_off );

        Tree::get_num<float>( L, "hotspot_x", hot_x );
        Tree::get_num<float>( L, "hotspot_y", hot_y );

        Tree::get_bool( L, "smoothen", smoothen );

        if( Tree::get_string( L, "path", path ) )
        {
            Tree::ImgPtr img = Tree::GetButler()->GetImage( path );

            if( img ) {
                img->SetSmooth( smoothen );

                spr->SetImage( *img );
                if( w != 0 && h != 0 ) {
                    spr->SetSubRect( sf::IntRect( x, y, x + w, y + h ) );
                    spr->SetCenter( hot_x, hot_y );
                }

                return true;
            }
        }
    }
    return false;
}

