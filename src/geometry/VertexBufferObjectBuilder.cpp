/*
 * VertexBufferObjectBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "VertexBufferObjectBuilder.hpp"

/** Creates a new builder. */
VertexBufferObjectBuilder::VertexBufferObjectBuilder() {
	reset();
}

/** Add a vertex attribute to the buffer. */
void VertexBufferObjectBuilder::addAttribute(const string &name, int size) {
	attributes.push_back(VertexAttribute(name, size));
}

/** Removes all state that was accumulated. */
void VertexBufferObjectBuilder::reset() {
	interleaved = true;
	usage = GL_STATIC_DRAW;
	capacity = 0;
	attributes.clear();
}

/** Change how many vertices the VBO will hold. */
void VertexBufferObjectBuilder::setCapacity(GLuint capacity) {
	if (capacity > 0) {
		this->capacity = capacity;
	} else {
		BasicException e;
		e << "[VertexBufferObjectBuilder] Capacity must be greater than 0!";
		throw e;
	}
}

/** Change whether vertex attributes will be interleaved. */
void VertexBufferObjectBuilder::setInterleaved(bool interleaved) {
	this->interleaved = interleaved;
}

/** Change the hint on how the VBO will be accessed and modified. */
void VertexBufferObjectBuilder::setUsage(GLenum usage) {
	switch (usage) {
	case GL_DYNAMIC_DRAW:
	case GL_STATIC_DRAW:
	case GL_STREAM_DRAW:
		this->usage = usage;
		break;
	default:
		BasicException e;
		e << "[VertexBufferObjectBuilder] Unexpected usage type!";
		throw e;
	}
}

/** @return VertexBufferObject that was built. */
VertexBufferObject* VertexBufferObjectBuilder::toVertexBuffer() {
	
	if (!isComplete()) {
		BasicException e;
		e << "[VertexBufferObjectBuilder] VBO is not complete!";
		throw e;
	}
	
	return new VertexBufferObject((*this));
}

// HELPERS

/** @return True if all required parts have been specified. */
bool VertexBufferObjectBuilder::isComplete() const {
	return (capacity > 0) && (!attributes.empty());
}

// GETTERS AND SETTERS

bool VertexBufferObjectBuilder::isInterleaved() const {
	return interleaved;
}

GLuint VertexBufferObjectBuilder::getCapacity() const {
	return capacity;
}

GLenum VertexBufferObjectBuilder::getUsage() const {
	return usage;
}

map<string,GLuint> VertexBufferObjectBuilder::getOffsets() const {
	
	map<string,GLuint> offsets;
	list<VertexAttribute>::const_iterator it;
	GLuint offset = 0;
	GLsizei attributeSizeInBytes;
	
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		offsets[it->getName()] = offset;
		attributeSizeInBytes = sizeof(GLfloat) * it->getComponents();
		if (isInterleaved()) {
			offset += attributeSizeInBytes;
		} else {
			offset += attributeSizeInBytes * getCapacity();
		}
	}
	return offsets;
}

/** @return Total number of bytes in the VertexBufferObject. */
GLsizei VertexBufferObjectBuilder::getSizeInBytes() const {
	
	list<VertexAttribute>::const_iterator it;
	GLsizei sizeInBytes = 0;
	
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		sizeInBytes += sizeof(float) * it->getComponents();
	}
	return sizeInBytes * getCapacity();
}

/** @return Number of bytes between consecutive vertices. */
GLuint VertexBufferObjectBuilder::getStrideInBytes() const {
	
	list<VertexAttribute>::const_iterator it;
	GLuint strideInBytes = 0;
	
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		strideInBytes += sizeof(float) * it->getComponents();
	}
	return strideInBytes;
}




