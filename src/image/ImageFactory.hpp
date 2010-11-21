/*
 * ImageFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_IMAGEFACTORY_HPP
#define GLOOP_IMAGEFACTORY_HPP
#include "gloop_common.h"
#include <edo/Path.hpp>
#include <edo/Text.hpp>
#include "Image.hpp"
#include "BmpImage.hpp"
using namespace std;


/** @brief Creates an image of the appropriate type.
 * 
 * @ingroup image
 */
class ImageFactory {
public:
	static Image* create(const string &filename);
};


#endif
