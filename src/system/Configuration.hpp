/*
 * Configuration.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_CONFIGURATION_HPP
#define GLOOP_CONFIGURATION_HPP
#include "gloop_common.h"
using namespace std;


/** @brief Retrieve and display OpenGL settings.
 * @ingroup graphics
 */
class Configuration {
public:
	static int getMaxColorAttachments();
	static int getMaxDrawBuffers();
protected:
	static string getString(GLenum flag);
	static int getInteger(GLenum flag);
};


#endif
