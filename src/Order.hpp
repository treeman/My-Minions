#pragma once

#include "Tree/Vec2D.hpp"

class Order {
public:
    struct CamNudgeOrder {
        int x, y;
    };

    struct Pos {
        int x, y;
    };

    enum OrderType {
        Move,
        CamNudge,
        AddPath,
        RemovePath,
        Chock,
        TogglePause,
        Pause,
        Unpause,
        SetSpeed,
    };

    OrderType type;

    union {
        CamNudgeOrder   cam_nudge;
        Pos             pos;
        int             sim_speed;
    };
};

class OrderHandler {
public:
    virtual ~OrderHandler() { }
    virtual void HandleOrder( Order order ) = 0;
};

