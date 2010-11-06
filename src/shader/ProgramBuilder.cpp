/*
 * ProgramBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ProgramBuilder.hpp"

/** Builds a program from a vertex and fragment shader. */
GLuint ProgramBuilder::build(GLuint vertShader, GLuint fragShader) {
	
	list<GLuint> shaders;
	
	shaders.push_back(vertShader);
	shaders.push_back(fragShader);
	return build(shaders);
}

/** Builds a program from several shaders. */
GLuint ProgramBuilder::build(list<GLuint> &shaders) {
	
	GLint linked;
	GLuint handle;
	list<GLuint>::iterator it;
	
	handle = glCreateProgram();
	for (it=shaders.begin(); it!=shaders.end(); ++it) {
		glAttachShader(handle, (*it));
	}
	
	glLinkProgram(handle);
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);
	if (!linked) {
		report(handle);
	}
	
	return handle;
}

/** Prints the log. */
void ProgramBuilder::report(GLuint handle) {
	
	GLchar *log;
	GLint count=0, returned=0;
	
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &count);
	log = new GLchar[count+1];
	glGetProgramInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	
	cout << log << endl;
	delete[] log;
}
