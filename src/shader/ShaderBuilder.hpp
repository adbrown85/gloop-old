/*
 * ShaderBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_SHADERBUILDER_HPP
#define GLOOP_SHADERBUILDER_HPP
#include "gloop_common.h"
#include <edo/Path.hpp>
#include "Preprocessor.hpp"
#include "Error.hpp"
using namespace std;


/** @brief Creates, loads, and compiles a shader.
 * @ingroup basic
 */
class ShaderBuilder {
public:
	static int build(const string &filename);
	static int build(GLenum type, const string &filename);
protected:
	static int create(GLenum type);
	static void compile(int handle, const string &filename, Code &code);
	static void load(int handle, const string &filename, Code &code);
};


#endif
