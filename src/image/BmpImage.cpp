/*
 * BmpImage.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BmpImage.hpp"

/** Creates a new bitmap image. */
BmpImage::BmpImage(const string &filename) : Image(filename) {
	
	this->data = NULL;
	
	load();
}

/** Destroys the bitmap image. */
BmpImage::~BmpImage() {
	
	if (data != NULL) {
		delete[] data;
	}
}

/** Loads the image into memory. */
void BmpImage::load() {
	
	BmpImageReader reader;
	
	reader.read(getFilename());
	
	setAlignment(reader.getAlignment());
	setWidth(reader.getWidth());
	setHeight(reader.getHeight());
	setFormat(reader.getFormat());
	setSize(reader.getSize());
	
	data = new GLubyte[getSize()];
	reader.toArray((char*)data, getSize());
}
