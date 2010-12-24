/*
 * Projection.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Projection.hpp"

/** @return Matrix representing a perspective projection. 
 * 
 * @param fovy Field of view angle, in degrees, in Y direction
 * @param aspect Aspect ratio to determine field of view in X direction
 * @param zNear Distance from viewer to near clipping plane (positive)
 * @param zFar Distance from viewer to far clipping plane (positive)
 * 
 * @throw BasicException if either Z distance is not greater than 0
 */
Matrix Projection::getPerspective(double fovy,
                                  double aspect,
                                  double zNear,
                                  double zFar) {
	
	double f;
	Matrix mat;
	
	if (zNear <= 0 || zFar <= 0) {
		BasicException e;
		e << "[Projection] Z distances must be positive!";
		throw e;
	}
	
	f = 1.0 / tan(Math::toRadians(fovy) / 2);
	
	mat(0,0) = f / aspect;
	mat(1,1) = f;
	mat(2,2) = (zFar + zNear) / (zNear - zFar);
	mat(2,3) = (2 * zFar * zNear) / (zNear - zFar);
	mat(3,2) = -1;
	
	return mat;
}
