#include "Tree/Butler.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Tweaks.hpp"

#include "Path.hpp"

Path::Path( IsoGrid *const _grid ) : grid( _grid )
{
    spr = BUTLER->CreateSprite( "gfx/empty.png" );
    charge = BUTLER->CreateSprite( "gfx/charge.png" );

    chock_time = TWEAKS->GetNum( "chock_time" );
}

bool Path::Has( Vec2i point )
{
    return points.count( point );
}

void Path::Add( Vec2i point )
{
    points.insert( point );
}

void Path::Remove( Vec2i point )
{
    points.erase( point );
}

void Path::Chock( Vec2i point )
{
    if( points.count( point ) ) {
        Charge charge;
        charge.point = point;
        charges.push_back( charge );
    }
}

void Path::Draw( int x_off, int y_off )
{
    for( Points::iterator it = points.begin(); it != points.end(); ++it ) {
        Vec2i pos = grid->GridToPixelPos( *it );
        pos.x -= x_off; pos.y -= y_off;

        spr.SetPosition( pos );
        Tree::Draw( spr );

        //std::stringstream s;
        //s << *it;
        //Tree::VisualDebug( s.str() );
    }

    for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
        Vec2i pos = grid->GridToPixelPos( it->point );
        pos.x -= x_off; pos.y -= y_off;

        charge.SetPosition( pos );
        Tree::Draw( charge );
    }
}

