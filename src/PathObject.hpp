#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Graphics.hpp"
#include "VisualObject.hpp"
#include "Charge.hpp"

class PathObject : public VisualObject {
public:
    PathObject() { }
    PathObject( sf::Sprite spr );
    virtual ~PathObject() { }

    void SetGridPos( Vec2i pos ) { gpos = pos; }
    Vec2i GetGridPos() const { return gpos; }

    virtual Charge ChargeIn( Charge &charge ) { return charge; }
    virtual Charge ChargeOut( Charge &charge ) { return charge; }

    virtual void Update( float dt ) { }
protected:
    void NewPos( Vec2i pos );
    void Render();

    Vec2i gpos;

    sf::Sprite spr;
};

typedef boost::shared_ptr<PathObject> PathObjPtr;

