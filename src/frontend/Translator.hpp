/*
 * Translator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "Identifiable.hpp"
#include "Manipulator.hpp"
#include "Matrix.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Selection.hpp"
#include "Shape.hpp"
#include "Translate.hpp"
#include "Vector.hpp"
#include "Window.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Tool for moving shapes.
 */
class Translator : public Manipulator {
public:
	Translator(float x, float y, float z);
	void draw() const;
	float findPixelFactor(Scene *scene, GLuint shapeID);
	void use(Scene *scene, const Vector &movement, GLuint shapeID);
private:
	GLUquadricObj *cone, *disk;
};


#endif
