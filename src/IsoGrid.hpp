#pragma once

#include <vector>

#include "Tree/Graphics.hpp"
#include "Tree/Vec2D.hpp"
#include "Tile.hpp"

class IsoGrid {
public:
    IsoGrid( int tiles_wide, int tiles_high, int tile_w, int tile_h );

    Vec2i PixelToGridPos( Vec2i pixel_pos );
    Vec2i PixelToGridPos( int pos_x, int pos_y );

    Vec2i GridToPixelPos( Vec2i grid_pos );
    Vec2i GridToPixelPos( int pos_x, int pos_y );

    Vec2i TopLeftPos( Vec2i grid_pos );
    Vec2i TopRightPos( Vec2i grid_pos );
    Vec2i DownLeftPos( Vec2i grid_pos );
    Vec2i DownRightPos( Vec2i grid_pos );

    bool IsPosValid( Vec2i world_pos );
    bool IsPosValid( int x, int y );

    bool IsGridPosValid( Vec2i grid_pos );
    bool IsGridPosValid( int x, int y );

    int TilesWide();
    int TilesHigh();

    int PixelsWide();
    int PixelsHigh();

    void SetPos( int x, int y );
    Vec2i GetPos();

    void Highlight( Vec2i grid_pos );

    TilePtr GetTile( Vec2i grid_pos );

    void Update( float dt );
    void Draw();
private:
    void RedrawAllTiles();

    int tiles_wide, tiles_high;
    int tile_w, tile_h;

    typedef std::vector<TilePtr> Tiles;
    Tiles tiles;

    sf::Sprite mouse_over_tile;

    Vec2i pos;
};

