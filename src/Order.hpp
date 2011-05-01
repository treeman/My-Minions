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

    struct Place {
        int x, y;
        int obj;
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
        PlaceObject,
    };

    OrderType type;

    union {
        CamNudgeOrder   cam_nudge;
        Pos             pos;
        float           sim_speed;
        Place           object;
    };
};

class OrderHandler {
public:
    virtual ~OrderHandler() { }
    virtual void HandleOrder( Order order ) = 0;
};

