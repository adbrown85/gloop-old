/*
 * VertexBuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "VertexBuffer.hpp"
int VertexBuffer::SIZEOF_VEC2 = sizeof(float) * 2;
int VertexBuffer::SIZEOF_VEC3 = sizeof(float) * 3;
int VertexBuffer::SIZEOF_VEC4 = sizeof(float) * 4;

/** Creates a new VBO.
 * 
 * @throw BasicException if prototype is not complete 
 */
VertexBuffer* VertexBuffer::newInstance(const VertexBufferPrototype &vbp) {
	
	if (!vbp.isComplete()) {
		BasicException e;
		e << "[VertexBufferObject] Prototype is not complete!";
		throw e;
	}
	
	return new VertexBuffer(vbp);
}

/** Creates a new VBO. */
VertexBuffer::VertexBuffer(const VertexBufferPrototype &vbp) : 
		BufferObject(GL_ARRAY_BUFFER) {
	
	offsets = vbp.getOffsets();
	count = vbp.getCapacity();
	interleaved = vbp.isInterleaved();
	usage = vbp.getUsage();
	size = vbp.getSizeInBytes();
	stride = vbp.getStrideInBytes();
	
	data = new GLubyte[size];
	current = data;
	end = data + size;
	
	bind();
	BufferObject::allocate(vbp.getUsage(), size);
	unbind();
	
	striding = 0;
}

/** Destroys the data held by the VBO. */
VertexBuffer::~VertexBuffer() {
	
	if (data != NULL) {
		delete[] data;
	}
}

/** Change the behavior after a put.
 * 
 * If striding is True, the VBO will automatically skip ahead to the next
 * vertex of the same attribute after a put.  Otherwise it will
 * just move past the attribute value as normal.
 * 
 * Use striding to update all the vertices of a single attribute.
 * 
 * @throw BasicException if not an interleaved vertex buffer object. 
 */
void VertexBuffer::setStriding(bool striding) {
	
	if (!isInterleaved()) {
		BasicException e;
		e << "[VertexBufferObject] Cannot use striding when not interleaved.";
		throw e;
	}
	
	if (striding) {
		this->striding = stride;
	} else {
		this->striding = 0;
	}
}

/** Flushes the data to the video card. */
void VertexBuffer::flush() {
	BufferObject::update(size, data, 0);
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBuffer::put(float x, float y) {
	
	if ((current + SIZEOF_VEC2) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*) current)[0] = x;
	((GLfloat*) current)[1] = y;
	current += (SIZEOF_VEC2 > striding ? SIZEOF_VEC2 : striding);
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBuffer::put(float x, float y, float z) {

	if ((current + SIZEOF_VEC3) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	current += (SIZEOF_VEC3 > striding ? SIZEOF_VEC3 : striding);
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBuffer::put(float x, float y, float z, float w) {
	
	if ((current + SIZEOF_VEC4) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	((GLfloat*)current)[3] = w;
	current += (SIZEOF_VEC4 > striding ? SIZEOF_VEC4 : striding);
}

/** Returns the current position to the beginning of the buffer. */
void VertexBuffer::rewind() {
	current = data;
}

/** Moves to the start of an attribute. */
void VertexBuffer::seek(const string &name) {
	
	map<string,GLuint>::iterator it;
	
	// Find offset and add it to data
	it = offsets.find(name);
	if (it != offsets.end()) {
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
GLuint VertexBuffer::getOffset(const string &name) const {
	
	map<string,GLuint>::const_iterator it;
	
	it = offsets.find(name);
	if (it != offsets.end()) {
		return it->second;
	} else {
		BasicException e;
		e << "[VertexBufferObject] Attribute '" << name << "' is not stored!";
		throw e;
	}
}



