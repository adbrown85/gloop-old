/*
 * UniformMatrix.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMMATRIX_HPP
#define UNIFORMMATRIX_HPP
#include "Uniform.hpp"
using namespace std;


/** @brief Container for GLSL matrix uniform variables.
 * @ingroup basic
 */
class UniformMatrix : public Uniform {
public:
	UniformMatrix(const Tag &tag);
	virtual void apply();
	virtual string toString() const;
private:
	GLfloat value[16];
	enum MatrixType{MODELVIEW, PROJECTION, MODELVIEW_PROJECTION,
	                NORMAL, IDENTITY};
	MatrixType matrixType;
	string as;
};


#endif
