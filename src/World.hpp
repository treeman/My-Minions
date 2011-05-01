#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Graphics.hpp"
#include "Tree/Log.hpp"

#include "IsoGrid.hpp"
#include "Order.hpp"
#include "Hero.hpp"
#include "Path.hpp"

class World : public OrderHandler {
public:
    World();

    void HandleOrder( Order order );

    Vec2f ConvertToWorld( Vec2f screen_pos ) const;
    Vec2f ConvertToWorld( float x, float y ) const {
        return ConvertToWorld( Vec2f( x, y ) );
    }

    Vec2f ConvertToScreen( Vec2f world_pos ) const;
    Vec2f ConvertToScreen( float x, float y ) const {
        return ConvertToScreen( Vec2f( x, y ) );
    }

    Vec2f GetCamPos() const;
    Vec2f NudgeCamX( Vec2f cam, int notches );
    Vec2f NudgeCamY( Vec2f cam, int notches );

    void CenterCam();
    void CenterCamOn( float x, float y );

    void Update( float dt );
    void Draw();
private:
    void UpdateCam( Vec2f new_cam );

    Vec2f cam;
    IsoGrid grid;

    Hero hero;

    Path path;
};

