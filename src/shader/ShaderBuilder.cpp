/*
 * ShaderBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShaderBuilder.hpp"

/** Builds a shader from @e filename. */
int ShaderBuilder::build(GLenum type, const string &filename) {
	
	int handle;
	Code code;
	
	handle = create(type);
	load(handle, filename, code);
	compile(handle, filename, code);
	return handle;
}

/** Requests a handle to a new GLSL shader of the correct type.
 * 
 * @throw BasicException if <i>type</i> is not supported.
 */
int ShaderBuilder::create(GLenum type) {
	
	switch (type) {
	case GL_FRAGMENT_SHADER:
	case GL_VERTEX_SHADER:
		return glCreateShader(type);
	default:
		BasicException e;
		e << "[Shader] Type not supported.";
		throw e;
	}
}

/** Loads a file into the Shader's source array and passes it to OpenGL. */
void ShaderBuilder::load(int handle, const string &filename, Code &code) {

	Code::iterator it;
	Preprocessor preprocessor;
	const char **source;
	int i, length;
	
	// Load file
	preprocessor.parse(filename);
	code = preprocessor.getCode();
	
	// Copy to source array
	length = code.size();
	source = new const char*[length];
	for (it=code.begin(); it!=code.end(); ++it) {
		i = distance(code.begin(), it);
		source[i] = it->text.c_str();
	}
	
	// Pass to OpenGL
	glShaderSource(handle, length, source, NULL);
}

/** Compiles the shader and prints the log.
 * 
 * @throw BasicException if the shader doesn't compile.
 */
void ShaderBuilder::compile(int handle, const string &filename, Code &code) {
	
	GLchar *log;
	GLint compiled, count, returned;
	
	// Compile
	glCompileShader(handle);
	
	// Print log
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &count);
	log = new GLchar[count+1];
	glGetShaderInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	Error::print(log, code);
	delete[] log;
	
	// Check
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		BasicException e;
		e << "[ShaderBuilder] '" << filename << "' did not compile." << endl;
		throw e;
	}
}

