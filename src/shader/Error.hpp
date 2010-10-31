/*
 * Error.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_ERROR_HPP
#define GLOOP_ERROR_HPP
#include "gloop_common.h"
#include <edo/Log.hpp>
#include <edo/Text.hpp>
#include "Code.hpp"
using namespace std;


/** @brief Utility for processing error messages.
 * @ingroup system
 */
class Error {
public:
	static void print(GLchar *log, Code &code);
protected: // Helpers
	static int findLine(const string &line);
	static string findMessage(const string &line);
	static bool fitsPattern(const string &line);
	static void printLine(const string &line, Code &code);
};


#endif
