/*
 * Texture3D.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture3D.hpp"


/**
 * Creates a new 3D texture.
 * 
 * @param name
 *     Name another node can reference.
 * @param filename
 *     Path to the file.
 */
Texture3D::Texture3D(string name,
                     string filename) : 
                     Texture(GL_TEXTURE_3D, name, filename),
                     dataset(filename) {
	
	// Initialize
	Texture3D::init();
}


/**
 * Creates a new 3D texture from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Texture3D::Texture3D(const Tag &tag) : 
                     Texture(GL_TEXTURE_3D, tag),
                     dataset(tag) {
	
	// Initialize
	Texture3D::init();
}


/**
 * Loads the texture on an available texture unit.
 */
void Texture3D::associate() {
	
	// Find the unit and load
	Texture::associate();
	load();
}


Texture3D* Texture3D::find(Node *node,
                           const string &name) {
	
	Node *current;
	Texture3D *texture3d;
	
	current = node->getParent();
	while (current != NULL) {
		texture3d = dynamic_cast<Texture3D*>(current);
		if (texture3d != NULL && texture3d->getName()==name) {
			return texture3d;
		} else {
			current = current->getParent();
		}
	}
	return NULL;
}


/**
 * Initializes attributes common to all constructors.
 */
void Texture3D::init() {
	
	// Initialize
	className = "Texture3D";
}


/**
 * Loads the dataset as a 3D texture.
 */
void Texture3D::load() {
	
	// Bind the texture to the right unit
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_3D);
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_3D, handle);
	
	// Pass the texture to OpenGL
	glTexImage3D(GL_TEXTURE_3D,           // Target
	             0,                       // Mipmap level
	             GL_LUMINANCE,            // Internal format
	             dataset.getWidth(),      // Width
	             dataset.getHeight(),     // Height
	             dataset.getDepth(),      // Depth
	             0,                       // Border
	             GL_LUMINANCE,            // Format
	             dataset.getType(),       // Type
	             dataset.getData());      // Data
	
	// Set parameters
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
}

