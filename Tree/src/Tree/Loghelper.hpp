#pragma once

#include <boost/shared_ptr.hpp>

#include "Tree/Log.hpp"
#include "Tree/InputHandler.hpp"
#include "Tree/Util.hpp"

namespace Tree
{
    class LogHelper;

    class LogHelper : public InputHandler {
    public:
        LogHelper();

        bool ShallLog() const;

        void SetLogKey( int key );
        bool HandleEvent( sf::Event &e );

        void EndofLoop();
    private:
        bool shall_log;
        int one_iteration_key;
    };
}

