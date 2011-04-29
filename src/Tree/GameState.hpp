#pragma once

#include "InputHandler.hpp"

namespace Tree
{
    class Game;

    class GameState : public InputHandler {
    public:
        virtual ~GameState() { }

        //called before we run it
        //may happen more than once if we don't destroy it between switcing
        virtual void Loaded() { }

        //same but before we unload it
        virtual void Unloaded() { }

        virtual void Update( float dt ) = 0;
        virtual void Draw() = 0;
    };
}

