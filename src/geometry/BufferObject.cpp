/*
 * BufferObject.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BufferObject.hpp"

/** Creates a new buffer object. */
BufferObject::BufferObject(GLenum type) {
	
	// Copy parameters
	this->type = type;
	
	// Generate
	glGenBuffers(1, &handle);
	bound = false;
}

/** Destroys the buffer object. */
BufferObject::~BufferObject() {
	
	glDeleteBuffers(1, &handle);
}

/** Use the buffer object. */
void BufferObject::bind() {
	
	glBindBuffer(type, handle);
	bound = true;
}

/** Stop using the buffer object. */
void BufferObject::unbind() {
	
	glBindBuffer(type, 0);
	bound = false;
}

/** Allocates enough room for the VBO. */
void BufferObject::allocate(GLenum usage, GLsizei size) {
	
	if (!isBound()) {
		BasicException e;
		e << "[BufferObject] Buffer must be bound to allocate";
		throw e;
	}
	
	glBufferData(type,                // target
				 size,                // size
				 NULL,                // data
				 usage);              // usage
}

/** Fills the buffer with data. */
void BufferObject::update(GLsizei size, GLvoid *data, int offset) {
	
	glBufferSubData(type,             // target
	                offset,           // offset
	                size,             // size
	                data);            // data
}
