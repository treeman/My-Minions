#ifndef VEC2D_HPP_INCLUDED
#define VEC2D_HPP_INCLUDED

#include <cmath>
#include <ostream>
#include <SFML/Graphics.hpp>

#include "Math.hpp"

template<typename T>
class Vec2D {
public:
    Vec2D( const T _x = 0, const T _y = 0 ) : x(_x), y(_y) { }

    Vec2D( const Vec2D &v ) { x = v.x; y = v.y; }
    template<typename S>
    Vec2D( const Vec2D<S> &v ) { x = v.x; y = v.y; }

    //implicit conversion between sfml's point type
    template<typename S>
    Vec2D( const sf::Vector2<S> &v ) { x = v.x; y = v.y; }
    template<typename S>
    operator sf::Vector2<S> () { return sf::Vector2<S>( x, y ); }

    Vec2D operator + ( const Vec2D &v ) const { return Vec2D( x + v.x, y + v.y ); }
    Vec2D operator - ( const Vec2D &v ) const { return Vec2D( x - v.x, y - v.y ); }
    Vec2D operator - () const { return Vec2D( -x, -y ); }
    Vec2D operator * ( T t ) const { return Vec2D( t * x, t * y ); }
    Vec2D operator / ( T t ) const { return Vec2D( x / t, y / t ); }

    void operator += ( const Vec2D &v ) { x += v.x; y += v.y; }
    void operator -= ( const Vec2D &v ) { x -= v.x; y -= v.y; }
    void operator *= ( T t ) { x *= t; y *= t; }
    void operator /= ( T t ) { x /= t; y /= t; }

    void operator = ( const Vec2D &v ) { x = v.x; y = v.y; }

    bool operator == ( const Vec2D &v ) const { return x == v.x && y == v.y; }
    bool operator != ( const Vec2D &v ) const { return !(*this == v); }

    T Dot( const Vec2D &v ) const { return x * v.x + y * v.y; }

    T Magnitude() const { return std::sqrt( x * x + y * y ); }
    T MagnitudeSq() const { return x * x + y * y; }

    void SetMagnitude( const T f ) {
        const T m = Magnitude();
        if( m == 0 ) return;
        x = f * x / m;
        y = f * y / m;
    }

    Vec2D Normalize() const {
        const T mag = Magnitude();
        if( mag == 0 ) return *this;
        else return (*this) / mag;
    }

    T x, y;

    //names for common vectors
    static const Vec2D zero;
    static const Vec2D right;
    static const Vec2D left;
    static const Vec2D up;
    static const Vec2D down;
};

typedef Vec2D<float> Vec2f;
typedef Vec2D<int> Vec2i;

template<typename T>
inline Vec2D<T> operator * ( const T f, const Vec2D<T> v ) {
    return f * v;
}

template<typename T>
inline std::ostream &operator << ( std::ostream &o, const Vec2D<T> &v ) {
    return o << v.x << "," << v.y;
}

template<typename T>
const Vec2D<T> Vec2D<T>::zero( 0, 0 );
template<typename T>
const Vec2D<T> Vec2D<T>::left( -1, 0 );
template<typename T>
const Vec2D<T> Vec2D<T>::right( 1, 0 );
template<typename T>
const Vec2D<T> Vec2D<T>::up( 0, -1 );
template<typename T>
const Vec2D<T> Vec2D<T>::down( 0, 1 );

#endif

