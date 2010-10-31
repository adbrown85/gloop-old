/*
 * Quaternion.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_QUATERNION_HPP
#define GLOOP_QUATERNION_HPP
#include "gloop_common.h"
#include <cmath>
#include <iomanip>
#include "Math.hpp"
#include "Matrix.hpp"
#include "Vec4.hpp"
using namespace std;


/** @brief Encapsulation of an axis/angle rotation that avoids gimbal lock.
 * @ingroup system
 */
class Quaternion {
public:
	Quaternion();
	Quaternion(float angle, const Vec4 &axis);
	Matrix getMatrix() const;
	Quaternion operator*(const Quaternion &B);
	void print();
	void set(float angle, const Vec4 &axis);
	void rotate(float angle, const Vec4 &axis);
	string toString() const;
protected:
	void normalize();
private:
	float s;
	Vec4 v;
};


#endif
