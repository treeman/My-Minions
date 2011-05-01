#include <boost/algorithm/string.hpp>

#include "Tree/Butler.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/Log.hpp"

#include "Path.hpp"

Path::Path( IsoGrid *const _grid ) : grid( _grid )
{
    spr = BUTLER->CreateSprite( "gfx/empty.png" );
    pos_charge = BUTLER->CreateSprite( "pos_charge" );
    neg_charge = BUTLER->CreateSprite( "neg_charge" );

    clock_time = TWEAKS->GetNum( "clock_time" );

    //charge_it = BUTLER->CreateSound( "snd/charge.wav" );
    dead_end = BUTLER->CreateSound( TWEAKS->GetString( "dead_end" ) );
    split = BUTLER->CreateSound( TWEAKS->GetString( "split" ) );
    turn = BUTLER->CreateSound( TWEAKS->GetString( "turn" ) );

    fnt = BUTLER->CreateString( "fnt/lucon.ttf", 12 );
    fnt.SetPosition( 68, Tree::GetWindowHeight() - 50 );
}

void Path::Start()
{
    t.Start();
    std::stringstream ss;
    ss << "Heartbeat rate: " << (int)(80 / clock_time);
    fnt.SetText( ss.str() );
}
void Path::Pause()
{
    t.Pause();
    fnt.SetText( "Puh, paused.." );
}

void Path::SetClockTime( float time )
{
    clock_time = time;
    std::stringstream ss;
    ss << "Heartbeat rate: " << (int)(80 / clock_time);
    fnt.SetText( ss.str() );
}

bool Path::Has( Vec2i point )
{
    return points.count( point );
}
bool Path::HasObj( Vec2i point )
{
    for( Objects::iterator it = objects.begin(); it != objects.end(); ++it ) {
        if( (*it)->GetGridPos() == point ) return true;
    }
    return false;
}
bool Path::IsCharged( Vec2i point )
{
    for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
        if( it->point == point ) { return true; }
    }
    return false;
}
bool Path::IsChocked( Vec2i point )
{
    for( Charges::iterator it = chocks.begin(); it != chocks.end(); ++it ) {
        if( it->point == point ) { return true; }
    }
    return false;
}

void Path::Rotate( Vec2i point )
{
    GetObj( point )->Rotate();
}

void Path::KillCharges()
{
    chocks.clear();
    charges.clear();
}

PathObjPtr Path::GetObj( Vec2i point )
{
    for( Objects::iterator it = objects.begin(); it != objects.end(); ++it ) {
        if( (*it)->GetGridPos() == point ) return *it;
    }
    throw Error::logical_fault( "couldn't find point" );
}

void Path::Add( Vec2i point )
{
    points.insert( point );
}

void Path::Add( PathObjPtr obj )
{
    const Vec2i pos = obj->GetGridPos();
    if( Has( pos ) && !HasObj( pos ) ) {
        //L_ << "Adding object" << pos << '\n';
        objects.push_back( obj );
    }
}

void Path::Remove( Vec2i point )
{
    if( IsChocked( point ) ) {
        for( Charges::iterator it = chocks.begin(); it != chocks.end(); ++it ) {
            if( it->point == point ) {
                charges.erase( it );
                return;
            }
        }
    }
    else if( IsCharged( point ) ) {
        for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
            if( it->point == point ) {
                charges.erase( it );
                return;
            }
        }
    }
    else if( HasObj( point ) ) {
        for( Objects::iterator it = objects.begin(); it != objects.end(); ++it ) {
            if( (*it)->GetGridPos() == point ) {
                objects.erase( it );
                return;
            }
        }
    }
    else {
        points.erase( point );
    }
}

bool Path::CanChock( Vec2i point )
{
    return points.count( point );
}

void Path::Chock( Vec2i point, Vec2i dir )
{
    AddChock( chocks, point, dir, 1 );
}

void Path::AddChock( Charges &charges, Vec2i point, Vec2i dir, int type )
{
    AddChock( charges, Charge( point, dir, type ) );
}
void Path::AddChock( Charges &charges, Charge chock )
{
    if( CanChock( chock.point ) ) {
        charges.push_back( chock );
    }
}

void Path::Update( float dt )
{
    const float curr_time = t.GetTime();
    if( curr_time > clock_time ) {
        Charges next_charges;

        for( Objects::iterator it = objects.begin(); it != objects.end(); ++it ) {
            if( (*it)->HasOutCharge() ) {
                const Vec2i pt = (*it)->GetGridPos();
                const Vec2i face = (*it)->Facing();

                //L_ << "We're " << pt << " " << face << '\n';

                Vec2i out_pos;
                if( face == Vec2i::left ) out_pos = grid->TopLeftPos( pt );
                else if( face == Vec2i::right ) out_pos = grid->DownRightPos( pt );
                else if( face == Vec2i::up ) out_pos = grid->TopRightPos( pt );
                else if( face == Vec2i::down ) out_pos = grid->DownLeftPos( pt );

                Charge charge = (*it)->ChargeOut();
                charge.point = out_pos;
                charge.can_kill = false;
                charge.dir = face;
                //L_ << "We wanna charge: " << charge.type << '\n';

                if( Has( out_pos ) ) {
                    //L_ << "Def added in next\n";
                    AddChock( next_charges, charge  );
                }

            }
            (*it)->ClockPulse();
        }


        for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
            if( it->can_kill ) continue;

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
                    AddChock( next_charges, order[0], dir[0], it->type );
                }
                else {
                    if( Has( order[1] ) || Has( order[2] ) ) {
                        AddChock( next_charges, order[1], dir[1], it->type );
                        AddChock( next_charges, order[2], dir[2], it->type );
                        if( Has( order[1] ) && Has( order[2] ) ) {
                            split.Play();
                        }
                        else {
                            turn.Play();
                        }
                    }
                    else {
                        AddChock( next_charges, order[3], dir[3], it->type );
                        dead_end.Play();
                    }
                }
            }
        }
        charges = next_charges;
        if( !chocks.empty() ) {
            //charge_it.Play();
            charges.splice( charges.begin(), chocks );
        }

        // This isn't effective, bot I don't care atm
        Charges unique;

        for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
            const Vec2i pt = it->point;

            if( HasObj( pt ) ) {
                PathObjPtr obj = GetObj( pt );
                obj->ChargeIn( *it );
            }

            bool has = false;
            for( Charges::iterator is = unique.begin(); is != unique.end(); ++is ) {
                if( *it == *is ) {
                    has = true;
                    break;
                }
            }
            if( !has ) { unique.push_back( *it ); }
        }
        charges = unique;

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

    for( Objects::iterator it = objects.begin(); it != objects.end(); ++it ) {
        Vec2i pos = grid->GridToPixelPos( (*it)->GetGridPos() );
        pos.x -= x_off; pos.y -= y_off;

        (*it)->SetPos( pos );
        (*it)->Draw();
    }

    for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
        Vec2i pos = grid->GridToPixelPos( it->point );
        pos.x -= x_off; pos.y -= y_off;

        if( it->type ) {
            pos_charge.SetPosition( pos );
            Tree::Draw( pos_charge );
        }
        else {
            neg_charge.SetPosition( pos );
            Tree::Draw( neg_charge );
        }
    }

    for( Charges::iterator it = chocks.begin(); it != chocks.end(); ++it ) {
        Vec2i pos = grid->GridToPixelPos( it->point );
        pos.x -= x_off; pos.y -= y_off;

        if( it->type ) {
            pos_charge.SetPosition( pos );
            Tree::Draw( pos_charge );
        }
        else {
            neg_charge.SetPosition( pos );
            Tree::Draw( neg_charge );
        }
    }

    const float h = Tree::GetWindowHeight();
    Tree::Draw( sf::Shape::Rectangle( 0, h - 60, 220, h, sf::Color::Black ) );

    Tree::Draw( fnt );
}

void Path::Save( std::fstream &file )
{
    file << "charges\n";
    for( Charges::iterator it = charges.begin(); it != charges.end(); ++it ) {
        file << it->point <<" "<< it->dir <<" "<< it->type <<"  "<<
            it->can_kill << '\n';
    }
    file << "points\n";

    for( Points::iterator it = points.begin(); it != points.end(); ++it ) {
        file << *it << " ";
    }
    file << '\n';
    file << "objects\n";

    for( Objects::iterator it = objects.begin(); it != objects.end(); ++it ) {
        file << (*it)->GetGridPos() << " " << (*it)->Facing() << " "
            << (*it)->GetObjNum() << '\n';
    }
}

void Path::Load( std::ifstream &file )
{
    //Charges
    while( !file.eof() )
    {
        if( str == "charges" ) continue;

        std::string str;
        std::getline( file, str );
        //if( str.size() == 0 ) {
        //L_ << "<" << str << '\n';
        if( str == "points" ) {
            //L_ << "It's done!\n";
            break;
        }
        else {
            std::vector<std::string> strs;
            boost::split( strs, str, boost::is_any_of("\t ") );

            Charge charge;
            L_ << "Charge: " << str << '\n';
        }
    }

    // Points
    while( !file.eof() )
    {
        std::string str;
        std::getline( file, str );
        //if( str.size() == 0 ) {
        //L_ << "<" << str << '\n';
        if( str == "objects" ) {
            //L_ << "It's done!\n";
            break;
        }
        else {
            L_ << "Points: " << str << '\n';
        }
    }

    //Objects
    while( !file.eof() )
    {
        std::string str;
        std::getline( file, str );
        //L_ << "<" << str << '\n';
        if( str.size() == 0 ) {
            //L_ << "It's done!\n";
            break;
        }
        else {
            L_ << "Object: " << str << '\n';
        }
    }
}

