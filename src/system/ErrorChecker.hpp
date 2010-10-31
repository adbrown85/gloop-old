/*
 * ErrorChecker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_ERRORCHECKER_HPP
#define GLOOP_ERRORCHECKER_HPP
#include "gloop_common.h"
#include <edo/Log.hpp>
#include <edo/BasicException.hpp>
using namespace std;


/** Utility for checking for OpenGL errors. */
class ErrorChecker {
public:
	static void assertNoError(const string &location);
	static void check(const string &location);
	static void clear();
private:
	static void report(GLenum error, const string &location);
	static string toString(GLenum error);
};


#endif
