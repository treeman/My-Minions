#include "Tree/Butler.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/Log.hpp"

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

void Path::Chock( Vec2i point, Vec2i dir )
{
    if( points.count( point ) ) {
        L_ << "Chocking: " << point << " -> " << dir << '\n';
        charges.push_back( Charge( point, dir ) );
    }
}

void Path::Update( float dt )
{
    for( Charges::iterator it = charges.begin(); it != charges.end(); ) {
        if( it->t.GetTime() > chock_time ) {
            const Vec2i pt = it->point;
            if( it->dir == Vec2i::zero ) {
                Chock( grid->TopLeftPos( pt ), Vec2i::left );
                Chock( grid->DownRightPos( pt ), Vec2i::right );
                Chock( grid->TopRightPos( pt ), Vec2i::up );
                Chock( grid->DownLeftPos( pt ), Vec2i::down );
            }
            else {
                Vec2i next_pt;
                if( it->dir == Vec2i::left ) {
                    next_pt = grid->TopLeftPos( pt );
                }
                else if( it->dir == Vec2i::right ) {
                    next_pt = grid->DownRightPos( pt );
                }
                else if( it->dir == Vec2i::up ) {
                    next_pt = grid->TopRightPos( pt );
                }
                else if( it->dir == Vec2i::down ) {
                    next_pt = grid->DownLeftPos( pt );
                }
                Chock( next_pt, it->dir );
            }
            Charges::iterator del = it;
            ++it;
            charges.erase( del );
        }
        ++it;
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

