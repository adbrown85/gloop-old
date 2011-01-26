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
	capacity = vbp.getCapacity();
	interleaved = vbp.isInterleaved();
	usage = vbp.getUsage();
	footprint = vbp.getSizeInBytes();
	stride = vbp.getStrideInBytes();
	
	data = new GLubyte[footprint];
	current = data;
	end = data + footprint;
	skip = false;
	
	bind();
	BufferObject::allocate(vbp.getUsage(), footprint);
	unbind();
}

/** Destroys the data held by the VBO. */
VertexBuffer::~VertexBuffer() {
	
	if (data != NULL) {
		delete[] data;
	}
}

/** Flushes the data to the video card. */
void VertexBuffer::flush() {
	BufferObject::update(footprint, data, 0);
	skip = false;
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBuffer::put(float x, float y) {
	
	if ((current + SIZEOF_VEC2) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*) current)[0] = x;
	((GLfloat*) current)[1] = y;
	current += skip ? stride : SIZEOF_VEC2;
}

/** Specifies the value of a vertex for the current attribute. */
void VertexBuffer::put(float x, float y, float z) {

	if ((current + SIZEOF_VEC3) > end) {
		throw BasicException("Put would exceed buffer.");
	}
	
	((GLfloat*)current)[0] = x;
	((GLfloat*)current)[1] = y;
	((GLfloat*)current)[2] = z;
	current += skip ? stride : SIZEOF_VEC3;
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
	current += skip ? stride : SIZEOF_VEC4;
}

/** Returns the current position to the beginning of the buffer. */
void VertexBuffer::rewind() {
	current = data;
	skip = false;
}

/** Moves to the start of an attribute.
 * 
 * In addition, when the buffer is interleaved, subsequent calls to any
 * of the put methods will cause the buffer's internal marker to jump
 * to the next vertex of the same attribute.  This method should be
 * used to update all vertices of a single attribute.  Normal behavior
 * will be restored after the buffer is rewound or flushed.
 */
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
	
	// Enable skipping
	skip = true;
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
