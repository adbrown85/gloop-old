/*
 * BufferObject.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_BUFFEROBJECT_HPP
#define GLOOP_BUFFEROBJECT_HPP
#include "gloop_common.h"
using namespace std;

/** @brief OpenGL buffer object.
 * 
 * @ingroup graphics
 */
class BufferObject {
public:
	BufferObject(GLenum type);
	virtual ~BufferObject();
	virtual void bind();
	virtual void unbind();
// Getters and setters
	virtual bool isBound() const;
	virtual GLuint getHandle() const;
	virtual GLenum getType() const;
protected:
	virtual void allocate(GLenum usage, GLsizei size);
	virtual void update(GLsizei size, GLvoid *data, int offset=0);
private:
	bool bound;
	GLuint handle;
	GLenum type;
};

/** @return OpenGL's underlying identifier for the buffer. */
inline GLuint BufferObject::getHandle() const {return handle;}

/** @return Type of the buffer. */
inline GLenum BufferObject::getType() const {return type;}

/** @return True if buffer is currently active. */
inline bool BufferObject::isBound() const {return bound;}

#endif
