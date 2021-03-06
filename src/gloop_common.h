/*
 * common.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_COMMON_H
#define GLOOP_COMMON_H

// Configuration file
#ifdef HAVE_CONFIG_H
#ifndef CONFIG_H
#define CONFIG_H
#include "config.h"
#endif
#endif

// C++ STL
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>

// GLEW
#ifdef HAVE_GLEW
#include <GL/glew.h>
#endif

// OpenGL
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#endif
