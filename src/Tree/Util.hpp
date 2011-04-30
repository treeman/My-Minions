#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <SFML/Window.hpp>

#include "Tree/Vec2D.hpp"

#define BUTLER Tree::GetButler()
#define TWEAKS Tree::GetTweaks()
#define SETTINGS Tree::GetSettings()

//make life easier
typedef std::vector<std::string> Strings;
typedef std::map<std::string, std::string> StringMap;

namespace Tree
{
    // A bunch of helper functions who fetch states from game
    extern float GetFPS();
    extern const sf::Input &GetInput();

    extern const int GetWindowWidth();
    extern const int GetWindowHeight();

    extern bool IsMouseValid();
    extern Vec2f GetMousePos();
    extern void SetMousePos( const Vec2f &pos );
    extern void SetMousePos( float x, float y );

    extern void VisualDebug( std::string str );
    extern void VisualDebug( std::string id, std::string str );
    extern void RemoveDebug( std::string id );

    class Butler;
    class Settings;
    class Tweaks;
    class LogHelper;

    //get classes from game
    boost::shared_ptr<Tree::Butler> GetButler();
    boost::shared_ptr<Tree::Settings> GetSettings();
    boost::shared_ptr<Tree::Tweaks> GetTweaks();
    boost::shared_ptr<Tree::LogHelper> GetLogHelper();
}

