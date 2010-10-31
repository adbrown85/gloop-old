/*
 * MatrixStack.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_MATRIXSTACK_HPP
#define GLOOP_MATRIXSTACK_HPP
#include "gloop_common.h"
#include <stack>
#include "Matrix.hpp"
using namespace std;


/** @brief Stack of matrices initialized with the identity matrix.
 * @ingroup graphics
 */
class MatrixStack {
public:
	MatrixStack();
	void push();
	void pop();
	Matrix& top();
private:
	stack<Matrix> matrices;
};

/** Makes a copy of the top of the stack and pushes it on. */
inline void MatrixStack::push() {matrices.push(top());}

/** Removes the top of the stack. */
inline void MatrixStack::pop() {matrices.pop();}

/** @return Top of the stack. */
inline Matrix& MatrixStack::top() {return matrices.top();}


#endif
