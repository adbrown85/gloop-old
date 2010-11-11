/*
 * ProgramAnalyzer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ProgramAnalyzer.hpp"

/** @return Names and types of all the active uniforms in @e program. */
map<string,UniformInfo> ProgramAnalyzer::listUniforms(GLuint program) {
	
	char *buffer;
	GLint count, size;
	map<string,UniformInfo> catalog;
	GLenum type;
	UniformInfo info;
	
	// Get count and size
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &size);
	
	// Make buffer
	buffer = new char[size+1];
	
	// Get info
	for (int i=0; i<count; ++i) {
		glGetActiveUniform(program,       // program
		                   i,             // index
		                   size,          // bufSize
		                   NULL,          // length
		                   &(info.count), // elements
		                   &(info.type),  // type
		                   buffer);       // name
		catalog[buffer] = info;
	}
	return catalog;
}

/** @return Text describing the type of a uniform variable .*/
string ProgramAnalyzer::getTypeName(GLenum type) {
	
	switch (type) {
	case GL_FLOAT:             return "float";
	case GL_FLOAT_VEC2:        return "vec2";
	case GL_FLOAT_VEC3:        return "vec3";
	case GL_FLOAT_VEC4:        return "vec4";
	case GL_INT:               return "int";
	case GL_INT_VEC2:          return "ivec2";
	case GL_INT_VEC3:          return "ivec3";
	case GL_INT_VEC4:          return "ivec4";
	case GL_BOOL:              return "bool";
	case GL_BOOL_VEC2:         return "bvec2";
	case GL_BOOL_VEC3:         return "bvec3";
	case GL_BOOL_VEC4:         return "bvec4";
	case GL_FLOAT_MAT2:        return "mat2";
	case GL_FLOAT_MAT3:        return "mat3";
	case GL_FLOAT_MAT4:        return "mat4";
	case GL_SAMPLER_1D:        return "sampler1D";
	case GL_SAMPLER_2D:        return "sampler2D";
	case GL_SAMPLER_3D:        return "sampler3D";
	case GL_SAMPLER_CUBE:      return "samplerCube";
	case GL_SAMPLER_1D_SHADOW: return "sampler1DShadow";
	case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
	}
}
