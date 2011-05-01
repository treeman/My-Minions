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

    int GetObjNum() { return obj_num; }
    void SetObjNum( int n ) { obj_num = n; }

    // Only one entrance
    void Rotate();
    Vec2i Facing();

    sf::Sprite GetSprite() { return spr; }

    virtual void Update( float dt ) { }
protected:
    virtual void ChargeOutSent() { }

    void NewPos( Vec2i pos );
    void Render();

    virtual bool ShowDirection() { return false; }

    Vec2i gpos;

    sf::Sprite spr;

    sf::Sprite right_dir;
    sf::Sprite left_dir;
    sf::Sprite up_dir;
    sf::Sprite down_dir;

    void QueueCharge( Charge &charge );
    bool has_charge;
    Charge out_charge;

    Vec2i face;

    int obj_num;
private:
    void Reset();
};

typedef boost::shared_ptr<PathObject> PathObjPtr;

