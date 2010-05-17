/*
 * Scale.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCALE_HPP
#define SCALE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Tag.hpp"
#include "Transformation.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Node that resizes items in the scene.
 */
class Scale : public Transformation,
              public Vector {
public:
	Scale(const Tag &tag);
	virtual void add(const Vector &B);
	virtual void apply();
	static Scale* find(Node *node);
	virtual void remove();
	virtual string toString() const;
private:
	float value;
};


#endif
