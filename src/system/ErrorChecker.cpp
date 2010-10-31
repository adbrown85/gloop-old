/*
 * ErrorChecker.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ErrorChecker.hpp"

/** Clears error state and throws an exception if there is an error. */
void ErrorChecker::assertNoError(const string &location) {
	
	GLenum error;
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		BasicException e;
		e << "At '" << location << "': " << toString(error);
		clear();
		throw e;
	}
}

/** Checks for an OpenGL error. */
void ErrorChecker::check(const string &location) {
	
	GLenum error;
	
	error = glGetError();
	while (error != GL_NO_ERROR) {
		report(error, location);
		error = glGetError();
	}
}

/** Clears all the error flags. */
void ErrorChecker::clear() {
	
	GLenum error;
	
	error = glGetError();
	while (error != GL_NO_ERROR) {
		error = glGetError();
	}
}

/** Print information about an error. */
void ErrorChecker::report(GLenum error, const string &location) {
	
	glog << "At '" << location << "':" << endl;
	glog << toString(error) << endl;
}

/** @return Human-readable description for an error. */
string ErrorChecker::toString(GLenum error) {

	switch (error) {
	case GL_INVALID_ENUM:
		return "Invalid enumeration.";
	case GL_INVALID_VALUE:
		return "Invalid value.";
	case GL_INVALID_OPERATION:
		return "Invalid operation.";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "Invalid framebuffer operation.";
	case GL_OUT_OF_MEMORY:
		return "Out of memory.";
	default:
		throw BasicException("[ErrorChecker] Unexpected error flag.");
	}
}

