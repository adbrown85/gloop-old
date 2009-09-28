/*
 * Texture.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <cassert>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include "Applicable.hpp"
#include "Node.hpp"
using namespace std;



/**
 * @brief
 *     OpenGL texture node.
 * @ingroup graph
 */
class Texture : public Node,
                public Applicable {
	
	
	public:
		
		Texture(string name,
		        string filename="");
		virtual void apply() = 0;
		virtual void associate();
		virtual void remove() = 0;
		virtual string toString() const;
		
		virtual string getFilename() const {return filename;}
		virtual GLuint getHandle() {return handle;}
		virtual string getName() const {return name;}
		virtual string getType() const {return type;}
		virtual int getUnit() const {return unit;}
	
	
	protected:
		
		GLuint handle;
		int unit;
		string filename, name, type;
		
		Texture();
};


#endif
