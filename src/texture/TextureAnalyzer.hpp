/*
 * TextureAnalyzer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_TEXTUREANALYZER_HPP
#define GLOOP_TEXTUREANALYZER_HPP
#include "gloop_common.h"
#include <edo/BasicException.hpp>
#include <edo/Log.hpp>
#include "PixelFormat.hpp"
using namespace std;


/** @brief Utility for analyzing textures.
 * @ingroup graphics
 */
class TextureAnalyzer {
public:    // Accessors
	GLint getBitsPerPixel();
	GLint getBytesPerPixel();
	GLenum getFormat();
	GLint getFootprint();
	GLint getWidth();
	GLint getHeight();
	GLint getDepth();
	bool isCompressed();
public:    // Mutators
	void setTexture(GLenum type, GLuint handle);
protected:
	GLint getRedSize();
	GLint getGreenSize();
	GLint getBlueSize();
	GLint getAlphaSize();
	GLint getRGBSize();
	GLint getRGBASize();
	GLint getLuminanceSize();
	GLint getFootprintCompressed();
	GLint getFootprintRaw();
private:
	GLenum type;
	GLuint handle;
};


#endif
