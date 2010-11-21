/*
 * ImageFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ImageFactory.hpp"

Image* ImageFactory::create(const string &filename) {
	
	string extension;
	
	extension = Text::toLower(Path::getExtension(filename));
	if (extension == "bmp") {
		return new BmpImage(filename);
	} else {
		ImageException e;
		e << "[ImageFactory] Image type not supported!";
		throw e;
	}
}

