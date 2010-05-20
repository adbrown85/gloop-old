/*
 * MouseClickHelper.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSECLICKHELPER_HPP
#define MOUSECLICKHELPER_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include "MouseHelper.hpp"
#include "Identifiable.hpp"
#include "Picker.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Handles mouse clicking actions for %Mouse.
 */
class MouseClickHelper : public MouseHelper {
public:
	MouseClickHelper(Interpreter *interpreter);
	virtual void onClick(int button, int state, int x, int y);
	virtual void setBindings(multimap<int,Binding> bindings);
	virtual void setManipulators(vector<Manipulator*> manipulators);
protected:
	void pickItem();
	void tryBindings();
	void tryBinding(Binding *binding);
private:
	Picker picker;
};


#endif
