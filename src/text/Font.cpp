/*
 * Font.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Font.hpp"

/** Create a new font. */
Font::Font(const string &family, Style style, int size) {
	
	this->family = family;
	this->style = style;
	this->size = size;
}

//--------------------------------------------------------
// Converters
//

/** @return String representation of this object. */
string Font::toString() const {
	
	ostringstream ss;
	
	ss << (*this);
	return ss.str();
}

//--------------------------------------------------------
// Operators
//

/** @return True if that equals this. */
bool Font::operator==(const Font &that) const {
	return size == that.size
			&& style == that.style
			&& family == that.family;
}

/** @return True if that is less than this. */
bool Font::operator<(const Font &that) const {
	
	int result;
	
	result = family.compare(that.family);
	if (result < 0) {
		return true;
	} else if (result > 0) {
		return false;
	}
	
	if (style < that.style) {
		return true;
	} else if (style > that.style) {
		return false;
	}
	
	if (size < that.size) {
		return true;
	} else if (size > that.size) {
		return false;
	}
	
	return false;
}

/** Insert font into an output stream. */
ostream& operator<<(ostream &os, const Font &font) {
	
	os << "Font";
	os << " family='" << font.family << "'";
	os << " style='" << font.style << "'";
	os << " size='" << font.size << "'";
	return os;
}
