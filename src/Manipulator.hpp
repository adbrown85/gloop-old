/*
 * Item.hpp
 *     Generic item class.  Also defines ItemSet.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __MANIPULATOR_HEADER__
#define __MANIPULATOR_HEADER__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Item.hpp"
#include "Scene.hpp"
#include "Vector.hpp"



class Manipulator : public Item  {
	
	
	public :
		
		virtual void use(Scene *scene, const Vector &difference) = 0;
		
		Vector getAxis() {return axis;}
	
	
	protected :
		
		Vector axis;
};


#endif
