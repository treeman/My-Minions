#include <boost/foreach.hpp>

#include "Tree/Log.hpp"
#include "Tree/Util.hpp"
#include "Tree/Butler.hpp"
#include "Tree/Settings.hpp"
#include "IsoGrid.hpp"

IsoGrid::IsoGrid( int x_tiles, int y_tiles, int tw, int th )
    : tiles_wide( x_tiles ), tiles_high( y_tiles ), tile_w( tw ), tile_h( th )
{
    mouse_over_tile = BUTLER->CreateSprite( "gfx/mouse_tile.png" );

    for( int x = 0; x < tiles_wide; ++x ) {
        for( int y = 0; y < tiles_high; ++y ) {
            const Vec2i pos = GridToPixelPos( x, y );
            const Vec2i grid_pos( x, y );

            sf::Sprite base;
            if( grid_pos.y & 1 ) {
                base = BUTLER->CreateSprite( "tile1" );
            }
            else {
                base = BUTLER->CreateSprite( "tile2" );
                //base = BUTLER->CreateSprite( "gfx/empty.png" );
            }
            TilePtr tile( new Tile( base, pos, tile_w, tile_h, grid_pos ) );
            tiles.push_back( tile );
        }
    }

    SETTINGS->Register<bool>( "debug_isogrid", false );
}

Vec2i IsoGrid::PixelToGridPos( Vec2i pos )
{
    //prevent negative values when searching our helper image
    if( pos.x < 0 || pos.y < 0 ) { return Vec2i( -1, -1 ); }

    const int region_x = int( pos.x / tile_w );
    const int region_y = int( pos.y / tile_h ) * 2;

    const int map_x = (int)pos.x % tile_w;
    const int map_y = (int)pos.y % tile_h;

    sf::Color map_col = mouse_over_tile.GetPixel( map_x, map_y );

    int region_dx, region_dy;
    if( map_col == sf::Color::Red ) {
        region_dx = -1;
        region_dy = -1;
    }
    else if( map_col == sf::Color::Yellow ) {
        region_dx = 0;
        region_dy = -1;
    }
    else if( map_col == sf::Color::White ) {
        region_dx = 0;
        region_dy = 0;
    }
    else if( map_col == sf::Color::Green ) {
        region_dx = -1;
        region_dy = 1;
    }
    else if( map_col == sf::Color::Blue ) {
        region_dx = 0;
        region_dy = 1;
    }
    else {
        //shouldn't happen
        L_ << "Nothing matched map_col in PixelToGridPos: " << pos << '\n';
        region_dx = 0;
        region_dy = 0;
    }

    const int tile_x = region_x + region_dx;
    const int tile_y = region_y + region_dy;

    if( IsGridPosValid( tile_x, tile_y ) ) {
        return Vec2i( tile_x, tile_y );
    }
    else {
        return Vec2i( -1, -1 );
    }
}

Vec2i IsoGrid::PixelToGridPos( int pos_x, int pos_y )
{
    return PixelToGridPos( Vec2i( pos_x, pos_y ) );
}

Vec2i IsoGrid::GridToPixelPos( Vec2i pos )
{
    const int overlap = tile_h / 2 + 0;
    const int y_offset = 0;
    const int plot_x = pos.x * tile_w + (pos.y & 1) * tile_h;
    const int plot_y = pos.y * overlap - y_offset;

    return Vec2i( plot_x, plot_y );
}
Vec2i IsoGrid::GridToPixelPos( int pos_x, int pos_y )
{
    return GridToPixelPos( Vec2i( pos_x, pos_y ) );
}

Vec2i IsoGrid::TopLeftPos( Vec2i grid_pos )
{
    if( grid_pos.y & 1 ) {
        return Vec2i( grid_pos.x, grid_pos.y - 1 );
    }
    else {
        return Vec2i( grid_pos.x - 1, grid_pos.y - 1 );
    }
}
Vec2i IsoGrid::TopRightPos( Vec2i grid_pos )
{
    if( grid_pos.y & 1 ) {
        return Vec2i( grid_pos.x + 1, grid_pos.y - 1 );
    }
    else {
        return Vec2i( grid_pos.x, grid_pos.y - 1 );
    }
}
Vec2i IsoGrid::DownLeftPos( Vec2i grid_pos )
{
    if( grid_pos.y & 1 ) {
        return Vec2i( grid_pos.x, grid_pos.y + 1 );
    }
    else {
        return Vec2i( grid_pos.x - 1, grid_pos.y + 1 );
    }
}
Vec2i IsoGrid::DownRightPos( Vec2i grid_pos )
{
    if( grid_pos.y & 1 ) {
        return Vec2i( grid_pos.x + 1, grid_pos.y + 1 );
    }
    else {
        return Vec2i( grid_pos.x, grid_pos.y + 1 );
    }
}

bool IsoGrid::IsPosValid( Vec2i world_pos )
{
    return IsPosValid( world_pos.x, world_pos.y );
}
bool IsoGrid::IsPosValid( int x, int y )
{
    const Vec2i grid_pos = PixelToGridPos( x, y );
    return grid_pos.x != -1 && grid_pos.y != -1;
}

bool IsoGrid::IsGridPosValid( Vec2i grid_pos )
{
    return IsGridPosValid( grid_pos.x, grid_pos.y );
}
bool IsoGrid::IsGridPosValid( int x, int y )
{
    return x >= 0 && y >= 0 && x < tiles_wide && y < tiles_high;
}

int IsoGrid::TilesWide()
{
    return tiles_wide;
}
int IsoGrid::TilesHigh()
{
    return tiles_high;
}

int IsoGrid::PixelsWide()
{
    return TilesWide() * tile_w + tile_w / 2;
}
int IsoGrid::PixelsHigh()
{
    return ( TilesHigh() + 1 ) / 2 * tile_h;
}

void IsoGrid::SetPos( int x, int y )
{
    const Vec2i new_pos( x, y );
    const Vec2i diff = pos - new_pos;

    for( Tiles::iterator it = tiles.begin(); it != tiles.end(); ++it ) {
        (*it)->Move( diff.x, diff.y );
    }
    pos = new_pos;
    Tree::ClearWindow();
}
Vec2i IsoGrid::GetPos()
{
    return pos;
}
void IsoGrid::Highlight( Vec2i grid_pos )
{
}

TilePtr IsoGrid::GetTile( Vec2i grid_pos )
{
    for( Tiles::iterator it = tiles.begin(); it != tiles.end(); ++it ) {
        const Vec2i tile_pos = (*it)->GetGridPos();
        if( tile_pos == grid_pos ) {
            return *it;
        }
    }
    throw( Error::logical_fault( "Damned blast trying to get an invalid tile!" ) );
}

void IsoGrid::Update( float dt )
{
    if( SETTINGS->GetValue<bool>( "debug_isogrid" ) ) {
        std::stringstream ss;
        ss << "isogrid's render offset: " << pos;
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "tiles: " << TilesWide() << "x" << TilesHigh();
        Tree::VisualDebug( ss.str() );
        ss.str("");

        ss << "dimensions: " << PixelsWide() << "x" << PixelsHigh();
        Tree::VisualDebug( ss.str() );
    }
}
void IsoGrid::Draw()
{
    for( Tiles::iterator it = tiles.begin(); it != tiles.end(); ++it ) {
        (*it)->Draw();
    }
}

void IsoGrid::RedrawAllTiles()
{
    for( Tiles::iterator it = tiles.begin(); it != tiles.end(); ++it ) {
        (*it)->Redraw();
    }
}

