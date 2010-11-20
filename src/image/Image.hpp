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

/** @brief Abstract class representing an image loaded from a file.
 * 
 * @ingroup image
 */
class Image {
public:
	Image(const string &filename);
	virtual ~Image() {}
	virtual GLchar* getData() const = 0;
// Getters and setters
	string getFilename() const;
	GLenum getFormat() const;
	int getWidth() const;
	int getHeight() const;
protected:
	void setFormat(GLenum format);
	void setWidth(int width);
	void setHeight(int height);
private:
	GLenum format;
	int width, height;
	string filename;
};

/** @return Name of the file the image was loaded from. */
inline string Image::getFilename() const {return filename;}

/** @return GL_RGB or GL_RGBA. */
inline GLenum Image::getFormat() const {return format;}

/** @return Size of the image in the X direction. */
inline int Image::getWidth() const {return width;}

/** @return Size of the image in the Y direction. */
inline int Image::getHeight() const {return height;}

inline void Image::setFormat(GLenum format) {this->format = format;}

inline void Image::setHeight(int height) {this->height = height;}

inline void Image::setWidth(int width) {this->width = width;}


#endif
