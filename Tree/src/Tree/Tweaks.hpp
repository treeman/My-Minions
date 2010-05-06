#pragma once

#include <string>
#include <map>

#include "Tree/Singleton.hpp"

#define TWEAKS Tree::Tweaks::Instance()

namespace Tree
{
    class Tweaks : public Tree::Singleton<Tweaks> {
    public:
        Tweaks();

        void Load( std::string path );
        double GetDouble( std::string s );
        std::string GetString( std::string s );
    private:
        typedef std::map<std::string, double> DoubleMap;
        DoubleMap doubles;
        typedef std::map<std::string, std::string> StringMap;
        StringMap strings;
    };
}
