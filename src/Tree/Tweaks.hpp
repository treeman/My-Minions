#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "Tree/Util.hpp"

namespace Tree
{
    class Tweaks {
    public:
        Tweaks();

        void Load( std::string path );
        double GetNum( std::string s );
        std::string GetString( std::string s );
    private:
        typedef std::map<std::string, double> DoubleMap;
        DoubleMap doubles;
        typedef std::map<std::string, std::string> StringMap;
        StringMap strings;
    };
}

