/*
 * ShaderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShaderFactory.hpp"
map<string,GLuint> ShaderFactory::shaders;

GLuint ShaderFactory::create(const string &filename) {
	
	map<string,GLuint>::iterator it;
	GLuint handle;
	
	// Check if already made
	it = shaders.find(filename);
	if (it != shaders.end()) {
		return it->second;
	}
	
	// Build it
	handle = ShaderBuilder::build(filename);
	shaders[filename] = handle;
	return handle;
}

GLuint ShaderFactory::create(GLenum type, const string &filename) {
	
	map<string,GLuint>::iterator it;
	GLuint handle;
	
	// Check if already made
	it = shaders.find(filename);
	if (it != shaders.end()) {
		return it->second;
	}
	
	// Build it
	handle = ShaderBuilder::build(type, filename);
	shaders[filename] = handle;
	return handle;
}

