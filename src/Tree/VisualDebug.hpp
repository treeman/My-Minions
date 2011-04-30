#pragma once

#include <string>
#include <vector>
#include <map>

#include "Tree/Graphics.hpp"
#include "Tree/DrawnLazy.hpp"

namespace Tree
{
    class Debug : public DrawnLazy {
    public:
        Debug();

        void Add( std::string s );
        void SetPersistent( std::string id, std::string s );
        void RemovePersistent( std::string id );

        void ResetTempStrings();
    private:
        void Render();

        Strings temp;
        StringMap persistent;

        sf::String render_str;
        const float x_pos;
        const float y_pos;
        const float line_height;
    };
}

