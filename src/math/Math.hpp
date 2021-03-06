/*
 * Math.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_MATH_HPP
#define GLOOP_MATH_HPP
#include "gloop_common.h"
#include <cmath>                        // sin, cos
#include "Vec4.hpp"                     // Storing points
using namespace std;


/** @brief Math-related utilities.
 * @ingroup system
 */
class Math {
public:
	static list<Vec4> computeCircle(float radius, int number);
	static double toRadians(double degrees);
public:
	static double PI;
};

/** Converts degrees to radians. */
inline double Math::toRadians(double deg) {return deg * Math::PI / 180;}


#endif
