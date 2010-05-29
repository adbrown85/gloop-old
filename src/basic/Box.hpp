/*
 * Box.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOX_HPP
#define BOX_HPP
#include "common.h"
#include "Hexahedron.hpp"
using namespace std;


/** @brief Six-sided shape with 2D texture coordinates for each face.
 * @ingroup basic
 */
class Box : public Hexahedron {
public:
	Box(const Tag &tag) : Hexahedron(tag,getTraits()) {};
protected:
	virtual void updateBufferCoords();
};


#endif
