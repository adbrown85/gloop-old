/*
 * Math.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Math.hpp"
double Math::PI=355.0/113;


/** Calculates the points in a circle.
 * 
 * @param radius Distance from center to a point
 * @param number Number of points in the circle
 * @return List of points in circle.
 */
list<Vec4> Math::computeCircle(float radius, int number) {
	
	double delta, theta, x, y;
	list<Vec4> points;
	
	// Initialize
	delta = 360.0 / number;
	
	// Calculate points
	points.push_back(Vec4(radius,0,0,1));
	theta = delta;
	while (theta < 360) {
		x = radius * cos(toRadians(theta));
		y = radius * sin(toRadians(theta));
		points.push_back(Vec4(x,y,0,1));
		theta += delta;
	}
	
	// Finish
	return points;
}

