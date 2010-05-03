/*
 * Uniform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORM_HPP
#define UNIFORM_HPP
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "Matrix.hpp"
#include "Node.hpp"
#include "Program.hpp"
#include "Tag.hpp"
#include "Text.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief
 *     Abstract base class for GLSL uniform variables.
 */
class Uniform : public Applicable {
public:
	Uniform(const Tag &tag);
	virtual void associate();
	virtual void apply() = 0;
	virtual void finalize();
	virtual void remove() {};
	virtual string toString() const;
protected:
	GLint location;
	Program *program;
	string link, name, type;
};


#endif