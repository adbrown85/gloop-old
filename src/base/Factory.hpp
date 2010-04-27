/*
 * Factory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include "Node.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup base
 * @brief
 *     Creates items from XML tags and adds them to the scene.
 */
class Factory {
	
	public:
		
		virtual Node* create(const Tag &tag) const = 0;
		virtual set<string> getTags() const;
	
	protected:
		
		set<string> tags;
};


inline set<string> Factory::getTags() const {return tags;}


#endif