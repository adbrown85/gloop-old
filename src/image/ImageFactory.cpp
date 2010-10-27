/*
 * ImageFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ImageFactory.hpp"


Image* ImageFactory::create(const string &filename) {
#ifdef HAVE_PIXBUFS
	return new ImagePixbuf(filename);
#else
	throw ImageException("[ImageFactory] Compiled without image support.");
#endif
}

