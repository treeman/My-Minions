#include "Sprite.hpp"
#include "Tree/Log.hpp"
#include "Tree/Butler.hpp"

#include <boost/foreach.hpp>

using Tree::SimpleSprite;
using Tree::SimpleAnimation;
using Tree::Sprite;
using Tree::SpriteLoader;

void SimpleSprite::Render( float x, float y )
{
    spr->SetColor( color );
    spr->Render( x + x_off, y + y_off );
}
void SimpleAnimation::Render( float x, float y )
{
    spr->SetColor( color );
    spr->Render( x + x_off, y + y_off );
}

Sprite::Sprite()
{

}

void Sprite::Update( float dt )
{
    BOOST_FOREACH( boost::shared_ptr<BaseSimpleSprite> s, sprites ) {
        s->Update( dt );
    }
}
void Sprite::Render( float x, float y )
{
    BOOST_FOREACH( boost::shared_ptr<BaseSimpleSprite> s, sprites ) {
        s->Render( x, y );
    }
}

SpriteLoader::SpriteLoader() { }

void SpriteLoader::Load( std::string lua_file ) throw( Error::lua_error & )
{
    LuaState L;

    if( luaL_dofile( L, lua_file.c_str() ) ) {
        const char *str = lua_tostring( L, -1 );
        lua_pop( L, -1 );
        throw( Error::lua_error( str ) );
    }

    lua_getglobal( L, "sprites" );
    for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) )
    {
        if( lua_istable( L, -1 ) ) {
            boost::shared_ptr<Sprite> sprite( new Sprite() );

            std::string name = lua_tostring( L, -2 );
            if( !LoadSprite( L, sprite ) ) {

                for( lua_pushnil( L ); lua_next( L, -2 ); lua_pop( L, 1 ) )
                {
                    LoadSprite( L, sprite );
                }
            }

            if( sprite->sprites.size() ) {
                sprite_map.insert( std::make_pair( name, sprite ) );
            }
        }
    }
}

boost::shared_ptr<Sprite> SpriteLoader::Get( std::string name )
{
    SpriteMap::iterator it = sprite_map.find( name );
    if( it == sprite_map.end() ) {
        throw( Error::sprite_not_found( ( "sprite " + name + " not found" ).c_str() ) );
    }
    else { return it->second; }
}

bool SpriteLoader::LoadSprite( lua_State *L, boost::shared_ptr<Sprite> spr )
{
    if( lua_istable( L, -1 ) ) {

        std::string path = "";
        float x = 0, y = 0;
        float w, h;
        float x_off = 0, y_off = 0;
        DWORD color = 0xffffffff;
        int frames = 0;
        float fps = 0;

        luah::get_num<float>( L, "x", x );
        luah::get_num<float>( L, "y", y );

        luah::get_num<float>( L, "x_off", x_off );
        luah::get_num<float>( L, "y_off", y_off );

        luah::get_num<DWORD>( L, "color", color );

        luah::get_num<int>( L, "frames", frames );
        luah::get_num<float>( L, "fps", fps );


        if( luah::get_num<float>( L, "w", w ) &&
            luah::get_num<float>( L, "h", h ) &&
            luah::get_string( L, "path", path ) )
        {
            TexObj tex = BUTLER->GetTex( path );

            if( tex ) {
                boost::shared_ptr<BaseSimpleSprite> simple;

                if( frames && fps ) {

                    boost::shared_ptr<SimpleAnimation> a( new SimpleAnimation() );
                    a->spr.reset( new hgeAnimation( tex, frames, fps, x, y, w, h ) );
                    simple = a;
                }
                else {
                    boost::shared_ptr<SimpleSprite> s( new SimpleSprite() );
                    s->spr.reset( new hgeSprite( tex, x, y, w, h ) );
                    simple = s;
                }

                simple->x_off = x_off; simple->y_off = y_off;
                simple->color = color;
                simple->tex = tex;

                spr->sprites.push_back( simple );

                return true;
            }
        }
    }
    return false;
}

