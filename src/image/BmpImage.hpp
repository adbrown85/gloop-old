/*
 * BmpImage.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BMPIMAGE_HPP
#define BMPIMAGE_HPP
#include "gloop_common.h"
#include <fstream>
#include "Image.hpp"
#include "BmpImageReader.hpp"

/** @brief Bitmap image.
 * 
 * @ingroup image
 */
class BmpImage : public Image {
public:
	BmpImage(const string &filename);
	virtual ~BmpImage();
// Getters and setters
	virtual GLchar* getData() const;
protected:
	virtual void load();
private:
	GLubyte *data;
};

/** @return Pointer to the pixels in the image. */
inline GLchar* BmpImage::getData() const {return (char*)data;}

#endif
