/*
 * Camera.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Camera.hpp"


/** Applies the camera position and rotation to the OpenGL modelview matrix. */
void Camera::apply() {
	
	State::setMode(VIEW_MODE);
	State::loadIdentity();
	State::apply(getViewMatrix());
}


Matrix Camera::getTranslationMatrix() const {
	
	return Matrix(1.0, 0.0, 0.0, position.x,
	              0.0, 1.0, 0.0, position.y,
	              0.0, 0.0, 1.0, position.z,
	              0.0, 0.0, 0.0, 1.0);
}


Matrix Camera::getViewMatrix() const {
	
	return getTranslationMatrix() * getRotationMatrix();
}


/** Initializes OpenGL. */
void Camera::load(int width, int height) {
	
	GLfloat array[16];
	Matrix matrix;
	
	// Set defaults
	reset();
	
	// Enable options
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	// Set up viewport
	glViewport(0, 0, width, height);
	matrix = Projection::getPerspective(30.0, (float)width/height, 0.8, 15.0);
	State::setMode(PROJECTION_MODE);
	State::loadIdentity();
	State::apply(matrix);
}


/** Moves the camera. */
void Camera::move(const Vec4 &amount) {
	
	position += amount;
}


/** Resets the camera's rotation and position. */
void Camera::reset() {
	
	// Reset transformations
	position.set(0.0, 0.0, CAMERA_DEFAULT_ZOOM);
	rotation.set(0.0, Vec4(0.0,1.0,0.0));
}


/** Rotates by axis/angle. */
void Camera::rotate(float angle, const Vec4 &axis) {
	
	rotation.rotate(angle, axis);
}


