/*
 * BitmapImage.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BITMAPIMAGE_HPP
#define BITMAPIMAGE_HPP
#include "gloop_common.h"
#include <fstream>
#include "Image.hpp"
#include "BitmapImageReader.hpp"

/** @brief Bitmap image.
 * 
 * @ingroup image
 */
class BitmapImage : public Image {
public:
	BitmapImage(const string &filename);
	virtual ~BitmapImage();
// Getters and setters
	virtual GLchar* getData() const;
protected:
	virtual void load();
private:
	GLubyte *data;
};

/** @return Pointer to the pixels in the image. */
inline GLchar* BitmapImage::getData() const {return (char*)data;}

#endif
