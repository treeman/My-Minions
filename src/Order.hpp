#pragma once

#include "Tree/Vec2D.hpp"

class Order {
public:
    struct MoveOrder {
        int x, y;
    };

    struct CamNudgeOrder {
        int x, y;
    };

    enum OrderType {
        Move,
        CamNudge,
    };

    OrderType type;

    union {
        MoveOrder       move;
        CamNudgeOrder   cam_nudge;
    };
};

class OrderHandler {
public:
    virtual ~OrderHandler() { }
    virtual void HandleOrder( Order order ) = 0;
};

