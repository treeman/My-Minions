#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Graphics.hpp"
#include "VisualObject.hpp"
#include "Charge.hpp"

class PathObject : public VisualObject {
public:
    PathObject() { }
    virtual ~PathObject() { }

    void SetGridPos( Vec2i pos ) { gpos = pos; }
    Vec2i GetGridPos() const { return gpos; }

    virtual Charge ChargeIn( Charge &charge ) { return charge; }
    virtual Charge ChargeOut( Charge &charge ) { return charge; }

    virtual void Update( float dt ) { }
protected:
    Vec2i gpos;
};

typedef boost::shared_ptr<PathObject> PathObjPtr;

