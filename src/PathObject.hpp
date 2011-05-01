#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Graphics.hpp"
#include "VisualObject.hpp"
#include "Charge.hpp"

class PathObject : public VisualObject {
public:
    PathObject();
    PathObject( sf::Sprite spr );
    virtual ~PathObject() { }

    void SetGridPos( Vec2i pos ) { gpos = pos; }
    Vec2i GetGridPos() const { return gpos; }

    virtual void ChargeIn( Charge &charge ) { }

    bool HasOutCharge() { return has_charge; }
    Charge ChargeOut();

    virtual void ClockPulse() { }

    // Only one entrance
    void Rotate();
    Vec2i Facing();

    sf::Sprite GetSprite() { return spr; }

    virtual void Update( float dt ) { }
protected:
    virtual void ChargeOutSent() { }

    void NewPos( Vec2i pos );
    void Render();

    Vec2i gpos;

    sf::Sprite spr;

    void QueueCharge( Charge &charge );
    bool has_charge;
    Charge out_charge;

    Vec2i face;

    void Reset();
};

typedef boost::shared_ptr<PathObject> PathObjPtr;

