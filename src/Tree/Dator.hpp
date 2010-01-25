#pragma once

#include <sstream>
#include <string>
#include <list>
#include <map>

#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

namespace Tree 
{
	class BaseDator {
	public:
		virtual ~BaseDator() { }
		
		virtual std::string Get() = 0;
		virtual std::string Set( const std::string new_val ) = 0;
	};
	
	class CallDator : public BaseDator {
	public:
		CallDator( boost::function<std::string()> func ) :
			call_func( func ) { }
			
		std::string Get() {
			return "";
		}
		std::string Set( const std::string ) {
			return call_func();
		}
	private:
		boost::function<std::string()> call_func;
	};
	
	template<typename T>
	class Dator : public BaseDator {
	public:
		Dator( T def_val ) : 
			val( def_val ), change_func(0) 
		{ }
		Dator( T def_val, boost::function<std::string( const T )> func ) :
			val( &def_val ), change_func( func )
		{ }
		virtual ~Dator() { }
		
		T Val() { return val; }
		
		std::string Get() {
			return boost::lexical_cast<std::string>( val );
		}
		std::string Set( const std::string new_val )
		{
			try {
				T call = boost::lexical_cast<T>( new_val );
				val = call;

				if( change_func ) {
					return change_func( call );
				}
			}
			catch( boost::bad_lexical_cast &e ) { }
			return "";
		}
	protected:
		T val;
		
		boost::function<std::string( const T )> change_func;
	};
	
	template<>
	class Dator<std::string> : public BaseDator {
	public:
		Dator( std::string def_val ) : 
			val( def_val ), change_func(0) 
		{ }
		Dator( std::string def_val, boost::function<std::string( const std::string )> func ) :
			val( def_val ), change_func( func )
		{ }
		virtual ~Dator() { }
		
		std::string Val() { return val; }
		std::string Get() { return val; }
		
		std::string Set( const std::string new_val )
		{
			val = new_val;
			if( change_func ) {
				return change_func( new_val );
			}
			return "";
		}
	protected:
		std::string val;
		boost::function<std::string( const std::string )> change_func;
	};

}
