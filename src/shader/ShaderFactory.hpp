/*
 * ShaderFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_SHADERFACTORY_HPP
#define GLOOP_SHADERFACTORY_HPP
#include "gloop_common.h"
#include "ShaderBuilder.hpp"
using namespace std;


class ShaderFactory {
public:
	static GLuint create(const string &type, const string &filename);
private:
	static map<string,GLuint> shaders;
	static ShaderBuilder builder;
};


#endif
