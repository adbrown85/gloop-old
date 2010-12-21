/*
 * VertexBufferObjectBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_VERTEXBUFFEROBJECTBUILDER_HPP
#define GLOOP_VERTEXBUFFEROBJECTBUILDER_HPP
#include "gloop_common.h"
#include "VertexBufferObject.hpp"


/** @brief <i>Builder</i> for a VertexBufferObject. */
class VertexBufferObjectBuilder : public VertexBufferPrototype {
public:
	VertexBufferObjectBuilder();
	virtual ~VertexBufferObjectBuilder() {}
	virtual void addAttribute(const string &name, int size);
	virtual void reset();
	virtual void setCapacity(GLuint capacity);
	virtual void setInterleaved(bool interleaved);
	virtual void setUsage(GLenum usage);
	virtual VertexBufferObject* toVertexBuffer();
// Getters
	virtual GLuint getCapacity() const;
	virtual bool isComplete() const;
	virtual bool isInterleaved() const;
	virtual GLenum getUsage() const;
	virtual GLsizei getSizeInBytes() const;
	virtual GLuint getStrideInBytes() const;
	virtual map<string,GLuint> getOffsets() const;
private:
	bool interleaved;
	GLenum usage;
	GLuint capacity; //FIXME: Should be GLsizei
	list<VertexAttribute> attributes;
};



#endif
