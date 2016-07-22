#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <math.h>

template<typename T> class Vector2D
{
public:
    Vector2D() : x(0), y(0) {};
    template<typename S> Vector2D(const Vector2D<S>& v) : x(v.x), y(v.y) {};
    template<typename S> Vector2D(S _x, S _y) : x(_x), y(_y) {};
    virtual ~Vector2D() {};

    template<typename S> void setValue(S _x, S _y){ x = _x; y = _y; }

    template<int N> double norm() { return pow(pow(x, N) + pow(y, N), 1.0 / (double)N); }
    template<> double norm<1>() { return ((x > 0) ? x : -x) + ((y > 0) ? y : -y); }
    template<> double norm<2>() { return sqrt(x * x + y * y); }
    double length() { return norm<2>(); }
    T length2() { return x * x + y * y; }

    Vector2D<double> ev() { double l = length(); return Vector2D<double>((double)x / l, (double)y / l); }

    template<typename S> operator Vector2D<S>() const { return Vector2D<S>(*this); }
    template<typename S> Vector2D<T>& operator=(const Vector2D<S>& v) { x = v.x; y = v.y; return *this; }

    template<typename S> bool operator==(const Vector2D<S>& v) { return (x == v.x) && (y == v.y); }
    template<typename S> bool operator!=(const Vector2D<S>& v) { return (x != v.x) || (y != v.y); }

    template<typename S> Vector2D<T>& operator+=(const Vector2D<S>& v) { x += v.x; y += v.y; return *this; }
    template<typename S> Vector2D<T>& operator-=(const Vector2D<S>& v) { x -= v.x; y -= v.y; return *this; }
    template<typename S> Vector2D<T>  operator+ (const Vector2D<S>& v) const { return (Vector2D<T>(*this) += v); }
    template<typename S> Vector2D<T>  operator- (const Vector2D<S>& v) const { return (Vector2D<T>(*this) -= v); }
    template<typename S> Vector2D<T>& operator*=(S v) { x *= v; y *= v; return *this; }
    template<typename S> Vector2D<T>& operator/=(S v) { x /= v; y /= v; return *this; }
    template<typename S> Vector2D<T>  operator* (S v) const { return (Vector2D<T>(*this) *= v); }
    template<typename S> Vector2D<T>  operator/ (S v) const { return (Vector2D<T>(*this) /= v); }
    // VS2012 bug template<typename S> friend Vector2D<T> operator*(int v1, const Vector2D<T>& v2) const { return (Vector2D<T>(v2) *= v1); }
    template<typename S> friend Vector2D<T> operator*(int v1, const Vector2D<T>& v2) { return (Vector2D<T>(v2) *= v1); }
    Vector2D<T> operator+() const { return Vector2D<T>(*this); }
    Vector2D<T> operator-() const { return Vector2D<T>(-x, -y); }

    template<typename S> double operator*(const Vector2D<S>& v) { return x * v.x + y * v.y; }

    T x, y;

};

typedef Vector2D<int>    Vector2Di;
typedef Vector2D<double> Vector2Df;

#endif // _VECTOR2D_H_
