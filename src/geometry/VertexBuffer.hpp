/*
 * VertexBuffer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_VERTEXBUFFER_HPP
#define GLOOP_VERTEXBUFFER_HPP
#include "gloop_common.h"
#include <edo/BasicException.hpp>
#include "BufferObject.hpp"
#include "VertexAttribute.hpp"
using namespace std;


/* Parameters to create a vertex buffer. */ 
class VertexBufferPrototype {
public:
	virtual bool isComplete() const = 0;
	virtual map<string,GLuint> getOffsets() const = 0;
	virtual GLuint getCapacity() const = 0;
	virtual bool isInterleaved() const = 0;
	virtual GLenum getUsage() const = 0;
	virtual GLsizei getSizeInBytes() const = 0;
	virtual GLuint getStrideInBytes() const = 0;
};

/** @brief OpenGL buffer object for vertex attributes.
 * 
 * To create a VertexBufferObject, use VertexBufferObjectBuilder.  Then 
 * use the variations of put() to fill the buffer.  Finally, call flush()
 * to send the data to the card.
 * 
 * To update data, call rewind() to go back to the beginning of the buffer and
 * then call the put() methods again to overwrite the data in the buffer.  
 * Remember to call flush() when you are done.
 * 
 * Lastly, if you would like to update just one attribute, call 
 * setStriding() before making any calls to put.  
 * 
 * @ingroup graphics
 */
class VertexBuffer : public BufferObject {
public:
	static VertexBuffer* newInstance(const VertexBufferPrototype &vbp);
	virtual ~VertexBuffer();
	void put(float x, float y);
	void put(float x, float y, float z);
	void put(float x, float y, float z, float w);
	void flush();
	void rewind();
	void seek(const string &name);
	void setStriding(bool striding);
	void dump();
// Getters and setters
	bool isInterleaved() const;
	GLuint getCapacity() const;
	GLsizei getSize() const;
	GLuint getOffset(const string &name) const;
	GLuint getStride() const;
private:
	bool interleaved;
	GLubyte *data, *current, *end;
	GLuint capacity, stride, striding;
	GLsizei size;
	GLenum usage;
	map<string,GLuint> offsets;
// Constants
	static int SIZEOF_VEC2, SIZEOF_VEC3, SIZEOF_VEC4;
// Constructors
	VertexBuffer(const VertexBufferPrototype &vbd);
};

/** @return Number of vertices the VBO can hold. */
inline GLuint VertexBuffer::getCapacity() const {return capacity;}

/** @return Size in bytes of the VBO. */
inline GLsizei VertexBuffer::getSize() const {return size;}

/** @return Number of bytes between vertices. */
inline GLuint VertexBuffer::getStride() const {return stride;}

/** @return True if this VBO keeps all attributes of a vertex together. */
inline bool VertexBuffer::isInterleaved() const {return interleaved;}


#endif
