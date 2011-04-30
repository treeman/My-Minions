#pragma once

#include "VisualObject.hpp"

class MoveableObject : public VisualObject {
public:
    MoveableObject();
    MoveableObject( Vec2i pos );
    virtual ~MoveableObject();

    bool IsMoving();
    Vec2f GetDestination();
    Vec2f GetOrigin();

    void MoveTowards( Vec2f pos );
protected:
    void UpdateMovement( float dt );
    void Init();

    Vec2i origin, destination;
    Vec2i move_dir;
    bool in_movement;
    float move_speed;
};

