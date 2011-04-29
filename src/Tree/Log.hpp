#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Tree/Singleton.hpp"

#define L_ (*Tree::Log::Instance())

namespace Tree {

    class Log : public Tree::Singleton<Log> {
    public:
        Log() { }
        ~Log()
        {
            if( file.is_open() ) {
                file.close();
            }
            std::cout << "Log file closed\n" << std::flush;
        }

        void Init( std::string logfile )
        {
            file.open( logfile.c_str() );
            std::cout << "Log file opened\n" << std::flush;
        }

        template<typename T>
        Log &operator << ( T var )
        {
            if( file.is_open() ) {
                file << var << std::flush;
            }
            std::cout << var << std::flush;

            return *this;
        }
    private:
        std::ofstream file;
    };
}

