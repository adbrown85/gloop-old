/*
 * Image.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_IMAGE_HPP
#define GLOOP_IMAGE_HPP
#include "gloop_common.h"
#include <edo/BasicException.hpp>
using namespace std;

/* Exception thrown from an image. */
class ImageException : public BasicException {
public:
	ImageException() {};
	ImageException(const ImageException &e) : BasicException(e) {}
	ImageException(const string &message) : BasicException(message) {}
};

/* Interface for an object that reads an image into memory. */
class ImageReader {
public:
	virtual void read(const string &filename) = 0;
	virtual void toArray(char* array, size_t size) = 0;
	virtual GLuint getAlignment() = 0;
	virtual GLenum getFormat() = 0;
	virtual GLuint getSize() = 0;
	virtual GLuint getWidth() = 0;
	virtual GLuint getHeight() = 0;
};

/** @brief Abstract class representing an image loaded from a file.
 * 
 * @ingroup image
 */
class Image {
public:
	Image(const string &filename);
	virtual ~Image() {}
	virtual GLchar* getData() const = 0;
// Getters
	GLuint getAlignment() const;
	string getFilename() const;
	GLenum getFormat() const;
	int getWidth() const;
	int getHeight() const;
	size_t getSize() const;
protected:
	void setAlignment(GLuint alignment);
	void setFormat(GLenum format);
	void setWidth(int width);
	void setHeight(int height);
	void setSize(size_t size);
private:
	GLenum format;
	int width, height;
	string filename;
	size_t size;
	GLuint alignment;
};

/** @return Number of bytes that row length should be multiples of. */
inline GLuint Image::getAlignment() const {return alignment;}

/** @return Name of the file the image was loaded from. */
inline string Image::getFilename() const {return filename;}

/** @return GL_RGB or GL_RGBA. */
inline GLenum Image::getFormat() const {return format;}

/** @return Size of the image in the X direction. */
inline int Image::getWidth() const {return width;}

/** @return Size of the image in the Y direction. */
inline int Image::getHeight() const {return height;}

/** @return Total number of bytes required to hold the pixel data. */
inline size_t Image::getSize() const {return size;}

inline void Image::setAlignment(GLuint align) {this->alignment = align;}

inline void Image::setFormat(GLenum format) {this->format = format;}

inline void Image::setHeight(int height) {this->height = height;}

inline void Image::setWidth(int width) {this->width = width;}

inline void Image::setSize(size_t size) {this->size = size;}


#endif
