/*
 * BitmapImage.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BitmapImage.hpp"

/** Creates a new bitmap image. */
BitmapImage::BitmapImage(const string &filename) : Image(filename) {
	
	this->data = NULL;
	
	load();
}

/** Destroys the bitmap image. */
BitmapImage::~BitmapImage() {
	
	if (data != NULL) {
		delete[] data;
	}
}

/** Loads the image into memory. */
void BitmapImage::load() {
	
	BitmapImageReader reader;
	
	reader.read(getFilename());
	
	setAlignment(reader.getAlignment());
	setWidth(reader.getWidth());
	setHeight(reader.getHeight());
	setFormat(reader.getFormat());
	setSize(reader.getSize());
	
	data = new GLubyte[getSize()];
	reader.toArray((char*)data, getSize());
}
