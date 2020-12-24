#pragma once
#include <void/math.h>
namespace vd {
template <typename T>
struct Point2D {
	T x;
	T y;

	Point2D(const Point2D& other) : x(other.x), y(other.y) {
	}
	Point2D(T ax = 0, T ay = 0) : x(ax), y(ay) {}
	
	Point2D operator +(const Point2D &point) const { return Point2D(x + point.x, y + point.y); };
    Point2D operator -(const Point2D &point) const { return Point2D(x - point.x, y - point.y); };
    Point2D operator *(T v) const { return Point2D(x * v, y * v); };
    void operator +=(const Point2D &point) { x += point.x; y += point.y; };
    void operator -=(const Point2D &point) { x -= point.x; y -= point.y; };
    
    void normalize()
    {
        T l = vd::sqrt(x * x + y * y);
        x /= l;
        y /= l;
    }
};



}