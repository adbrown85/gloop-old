/*
 * ImageFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_IMAGEFACTORY_HPP
#define GLOOP_IMAGEFACTORY_HPP
#include "gloop_common.h"
#include "Image.hpp"
#include "ImagePixbuf.hpp"
using namespace std;


/** @brief Creates an image of the appropriate type.
 * @ingroup graphics
 */
class ImageFactory {
public:
	static Image* create(const string &filename);
};


#endif
