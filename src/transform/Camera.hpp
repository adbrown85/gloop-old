/*
 * Camera.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_CAMERA_HPP
#define GLOOP_CAMERA_HPP
#include "gloop_common.h"
#include <GL/glu.h>
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vec4.hpp"
#include "State.hpp"
#define CAMERA_DEFAULT_ZOOM -10.0
#define CAMERA_ROTATE_AMOUNT 5.0
using namespace std;


/** @brief Encapsulation of rotation and position for a view.
 * @ingroup graphics
 */
class Camera {
public:
	void apply();
	Vec4 getPosition() const;
	Matrix getRotation() const;
	Matrix getRotationMatrix() const;
	Matrix getTranslationMatrix() const;
	Matrix getViewMatrix() const;
	void load(int width, int height);
	void move(const Vec4 &amount);
	void reset();
	void rotate(float angle, const Vec4 &axis);
private:
	Quaternion rotation;
	Vec4 position;
};

/** @return Position of the camera. */
inline Vec4 Camera::getPosition() const {return position;}

/** @return Rotation of the camera. */
inline Matrix Camera::getRotation() const {return rotation.getMatrix();}

/** @return Rotation of the camera as a matrix. */
inline Matrix Camera::getRotationMatrix() const {return rotation.getMatrix();}



#endif
