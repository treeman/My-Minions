#pragma once

#include <exception>
#include <stdexcept>
#include <string>

namespace Error
{
    class my_exception : public std::exception {
    public:
        my_exception( const std::string err ) : s( err ) { }
        virtual ~my_exception() throw() { }
        virtual const char *what() const throw() {
            return s.c_str();
        }
    protected:
        const std::string s;
    };

    class resource_not_found : public my_exception {
    public:
        resource_not_found( std::string err ) : my_exception( err ) { }
    };

    class setting_not_found : public my_exception {
    public:
        setting_not_found( std::string err ) : my_exception( err ) { }
    };

    class lua_error : public my_exception {
    public:
        lua_error( std::string err ) : my_exception( err ) { }
    };

    class logical_fault : public my_exception {
    public:
        logical_fault( std::string err ) : my_exception( err ) { }
    };
}

