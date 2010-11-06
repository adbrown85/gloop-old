/*
 * ProgramBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PROGRAMBUILDER_HPP
#define PROGRAMBUILDER_HPP
#include "gloop_common.h"
using namespace std;

/** @brief Utility for building shader programs.
 * 
 * @ingroup shader
 */
class ProgramBuilder {
public:
	static GLuint build(list<GLuint> &shaders);
protected:
	static void report(GLuint handle);
};

#endif
