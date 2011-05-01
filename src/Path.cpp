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

    charge_it = BUTLER->CreateSound( "snd/charge.wav" );
    dead_end = BUTLER->CreateSound( "snd/deadend.wav" );
    split = BUTLER->CreateSound( "snd/split.wav" );
    turn = BUTLER->CreateSound( "snd/turn.wav" );

    t.Start();
}

void Path::Start()
{
    t.Start();
}
void Path::Pause()
{
    t.Pause();
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

Path::Points Path::Neighbours( Vec2i pt )
{
    Points neighbours;

    const Vec2i left = grid->TopLeftPos( pt );
    const Vec2i right = grid->TopLeftPos( pt );
    const Vec2i up = grid->TopLeftPos( pt );
    const Vec2i down = grid->TopLeftPos( pt );

    if( Has( left ) ) neighbours.insert( left );
    if( Has( right ) ) neighbours.insert( right );
    if( Has( up ) ) neighbours.insert( up );
    if( Has( down ) ) neighbours.insert( down );

    return neighbours;
}

bool Path::CanChock( Vec2i point )
{
    return points.count( point );
}

void Path::Chock( Vec2i point, Vec2i dir )
{
    AddChock( chocks, point, dir );
}

void Path::AddChock( Charges &charges, Vec2i point, Vec2i dir )
{
    if( CanChock( point ) ) {
        charges.push_back( Charge( point, dir ) );
    }
}

void Path::Update( float dt )
{
    const float curr_time = t.GetTime();
    if( curr_time > chock_time ) {
        Charges next_charges;

        for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
            const Vec2i pt = it->point;
            if( it->dir == Vec2i::zero ) {
                Chock( grid->TopLeftPos( pt ), Vec2i::left );
                Chock( grid->DownRightPos( pt ), Vec2i::right );
                Chock( grid->TopRightPos( pt ), Vec2i::up );
                Chock( grid->DownLeftPos( pt ), Vec2i::down );
            }
            else {
                const Vec2i left = grid->TopLeftPos( pt );
                const Vec2i right = grid->DownRightPos( pt );
                const Vec2i up = grid->TopRightPos( pt );
                const Vec2i down = grid->DownLeftPos( pt );

                Vec2i order[4];
                Vec2i dir[4];

                if( it->dir == Vec2i::left ) {
                    order[0] = left; dir[0] = Vec2i::left;
                    order[1] = down; dir[1] = Vec2i::down;
                    order[2] = up; dir[2] = Vec2i::up;
                    order[3] = right; dir[3] = Vec2i::right;
                }
                else if( it->dir == Vec2i::right ) {
                    order[0] = right; dir[0] = Vec2i::right;
                    order[1] = down; dir[1] = Vec2i::down;
                    order[2] = up; dir[2] = Vec2i::up;
                    order[3] = left; dir[3] = Vec2i::left;
                }
                else if( it->dir == Vec2i::up ) {
                    order[0] = up; dir[0] = Vec2i::up;
                    order[1] = left; dir[1] = Vec2i::left;
                    order[2] = right; dir[2] = Vec2i::right;
                    order[3] = down; dir[3] = Vec2i::down;
                }
                else if( it->dir == Vec2i::down ) {
                    order[0] = down; dir[0] = Vec2i::down;
                    order[1] = left; dir[1] = Vec2i::left;
                    order[2] = right; dir[2] = Vec2i::right;
                    order[3] = up; dir[3] = Vec2i::up;
                }

                if( CanChock( order[0] ) ) {
                    AddChock( next_charges, order[0], dir[0] );
                }
                else {
                    if( Has( order[1] ) || Has( order[2] ) ) {
                        AddChock( next_charges, order[1], dir[1] );
                        AddChock( next_charges, order[2], dir[2] );
                        if( Has( order[1] ) && Has( order[2] ) ) {
                            split.Play();
                        }
                        else {
                            turn.Play();
                        }
                    }
                    else {
                        AddChock( next_charges, order[3], dir[3] );
                        dead_end.Play();
                    }
                }
            }
        }

        charges = next_charges;
        if( !chocks.empty() ) {
            charge_it.Play();
            charges.splice( charges.begin(), chocks );
        }
        t.Restart();
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

