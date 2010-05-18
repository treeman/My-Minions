#pragma once

#include "Tree/Log.hpp"
#include "Tree/InputHandler.hpp"
#include "Tree/Singleton.hpp"

#define LOGHELPER Tree::LogHelper::Instance()

namespace Tree
{
    class LogHelper : public Singleton<LogHelper>, public InputHandler {
    public:
        LogHelper() : shall_log( false ), one_iteration_key( 0 )
        { }

        bool ShallLog() const { return shall_log; }

        void SetLogKey( int key ) { one_iteration_key = key; }
        bool HandleEvent( hgeInputEvent &e )
        {
            if( e.type == INPUT_KEYDOWN && e.key == one_iteration_key ) {
                shall_log = true;
            }
        }

        void EndofLoop() { shall_log = false; }
    private:
        bool shall_log;
        int one_iteration_key;
    };
}

