/*
 * Font.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FONT_HPP
#define FONT_HPP
#include "gloop_common.h"
using namespace std;


/** @brief Information about how to depict text. */
class Font {
public:
	enum Style { PLAIN, BOLD, ITALIC };
	Font(const string &family, Style style, int size);
	virtual ~Font() { }
// Getters
	string getFamily() const;
	Style getStyle() const;
	int getSize() const;
// Converters
	string toString() const;
// Operators
	bool operator==(const Font &that) const;
	bool operator<(const Font &that) const;
	friend ostream& operator<<(ostream &os, const Font &font);
private:
	string family;
	Style style;
	int size;
};

inline string Font::getFamily() const {return family;}

inline Font::Style Font::getStyle() const {return style;}

inline int Font::getSize() const {return size;}

#endif
