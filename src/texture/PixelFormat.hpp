/*
 * PixelFormat.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_PIXELFORMAT_HPP
#define GLOOP_PIXELFORMAT_HPP
#include "gloop_common.h"
#include <edo/BasicException.hpp>
using namespace std;


/** @brief Utility for working with formats for textures and buffers.
 * @ingroup graphics
 */
class PixelFormat {
public:
	static GLenum getFormat(const string &name);
	static string getFormat(GLenum code);
	static GLenum getCompressedFormat(GLenum code);
protected: // Helpers
	static void addFormat(const string &name, GLenum code);
	static void load();
	static void loadNameConversions();
	static void loadCompressConversions();
private:   // Data
	static bool loaded;
	static map<string,GLenum> namesToCodes;
	static map<GLenum,string> codesToNames;
	static map<GLenum,GLenum> codesToCompressCodes;
};


#endif
