/*
 * Projection.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PROJECTION_HPP
#define PROJECTION_HPP
#include "gloop_common.h"
#include "Matrix.hpp"
#include "Math.hpp"

/** @brief Utility for calculating projection matrices.
 * 
 * @ingroup transform 
 */
class Projection {
public:
	static Matrix getPerspective(double fov, double asp, double n, double f);
};

#endif
