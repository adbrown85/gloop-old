/*
 * VertexBufferObject.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "VertexBufferObject.hpp"
int VertexBufferObject::SIZEOF_VEC2 = sizeof(float) * 2;
int VertexBufferObject::SIZEOF_VEC3 = sizeof(float) * 3;
int VertexBufferObject::SIZEOF_VEC4 = sizeof(float) * 4;


/** Creates a new VBO. */
VertexBufferObject::VertexBufferObject() : BufferObject(GL_ARRAY_BUFFER) {
	
	this->interleaved = true;
	this->count = 0;
	this->size = 0;
	this->stride = 0;
	this->autoStride = 0;
	data = NULL;
	current = NULL;
	end = NULL;
}

/** Destroys the data held by the VBO. */
VertexBufferObject::~VertexBufferObject() {
	
	if (data != NULL) {
		delete[] data;
	}
}

/** Adds a vertex attribute to the VBO. */
void VertexBufferObject::addAttribute(const string &name, int components) {
	
	attributes.push_back(VertexAttribute(name, components));
}

/** Allocates space for the VBO.
 * 
 * @note Disables striding. 
 */
void VertexBufferObject::allocate(GLenum usage, GLuint count) {
	
	list<VertexAttribute>::iterator it;
	GLuint position;
	
	// Check size
	if (attributes.empty()) {
		BasicException e;
		e << "[VertexBufferObject] No attributes were added!" << endl;
		throw e;
	}
	
	// Reset
	this->count = count;
	positions.clear();
	
	// Compute size and positions
	position = 0;
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		positions[it->getName()] = position;
		position += sizeof(GLfloat) * it->getComponents();
	}
	size = position * count;
	stride = size / count;
	
	// Recompute positions if not interleaved
	if (!isInterleaved()) {
		for (it=attributes.begin(); it!=attributes.end(); ++it) {
			positions[it->getName()] *= count;
		}
	}
	
	// Allocate local and GPU copy
	data = new GLubyte[size];
	current = data;
	end = data + size;
	BufferObject::allocate(usage, size);
}

/** Move to the next vertex of the same attribute after a put.
 * 
 * @throw BasicException if not an interleaved vertex buffer object. 
 */
void VertexBufferObject::enableAutoStriding() {
	
	if (!isInterleaved()) {
		BasicException e;
		e << "[VertexBufferObject] Cannot use striding when not interleaved.";
		throw e;
	}
	
	if (!isAllocated()) {
		BasicException e;
		e << "[VertexBufferObject] Cannot set striding before allocated.";
	}
	
	autoStride = stride;
}

/** Move to the next vertex in the buffer after a put. */
void VertexBufferObject::disableAutoStriding() {
	
	autoStride = 0;
}

/** Flushes the data to the video card. */
void VertexBufferObject::flush() {
	
	if (isAllocated()) {
		BufferObject::update(size, data, 0);
	} else {
		BasicException e;
		e << "[VertexBufferObject] Cannot flush before being allocated.";
		throw e;
	}
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBufferObject::put(float x, float y) {
	
	if ((current + SIZEOF_VEC2) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	current += SIZEOF_VEC2 + autoStride;
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBufferObject::put(float x, float y, float z) {

	if ((current + SIZEOF_VEC3) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	current += SIZEOF_VEC3 + autoStride;
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBufferObject::put(float x, float y, float z, float w) {
	
	if ((current + SIZEOF_VEC4) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	((GLfloat*)current)[3] = w;
	current += SIZEOF_VEC4 + autoStride;
}

/** Returns the current position to the beginning of the buffer. */
void VertexBufferObject::rewind() {
	
	current = data;
}

/** Set whether all all attributes for a vertex will be kept together. */
void VertexBufferObject::setInterleaved(bool interleaved) {
	
	if (!isAllocated()) {
		this->interleaved = interleaved;
	} else {
		BasicException e;
		e << "[VertexBufferObject] Cannot change interleave after allocated.";
		throw e;
	}
}

/** Moves to the start of an attribute. */
void VertexBufferObject::seek(const string &name) {
	
	map<string,GLuint>::iterator it;
	
	// Find position and add it to data
	it = positions.find(name);
	if (it != positions.end()) {
		current = data + it->second;
	} else {
		BasicException e;
		e << "[VertexBufferObject] Attribute '" + name + "' not stored.";
		throw e;
	}
}

// GETTERS AND SETTERS

/** @return Position of attribute @e name in the VBO.
 * 
 * @throw BasicException if @e name is not an attribute in the VBO 
 */
GLuint VertexBufferObject::getOffset(const string &name) const {
	
	map<string,GLuint>::const_iterator it;
	
	it = positions.find(name);
	if (it != positions.end()) {
		return it->second;
	} else {
		BasicException e;
		e << "[VertexBufferObject] Attribute '" << name << "' is not stored!";
		throw e;
	}
}
