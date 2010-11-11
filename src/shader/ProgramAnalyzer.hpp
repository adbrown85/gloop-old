/*
 * ProgramAnalyzer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PROGRAMANALYZER_HPP
#define PROGRAMANALYZER_HPP
#include "gloop_common.h"
#include "ShaderBuilder.hpp"
#include "ProgramBuilder.hpp"
using namespace std;


/* Information about a uniform. */
struct UniformInfo {
	GLenum type;
	GLint count;
};

/** @brief Utility for getting information about a shader program.
 * 
 * @ingroup shader 
 */
class ProgramAnalyzer {
public:
	static map<string,UniformInfo> listUniforms(GLuint program);
	static string getTypeName(GLenum type);
};

#endif
