/*
 * Preprocessor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_PREPROCESSOR_HPP
#define GLOOP_PREPROCESSOR_HPP
#include "gloop_common.h"
#include <fstream>
#include <iomanip>
#include <edo/BasicException.hpp>
#include <edo/Path.hpp>
#include <edo/Text.hpp>
#include "Code.hpp"
using namespace std;


/** @brief Utility for preprocessing C-like code.
 * 
 * Basically, %Preprocessor simply looks through C-like code and performs a few 
 * simple operations.  First, if it finds an @e include directive, it replaces 
 * that line with the lines from the appropriate file.  Lastly, it strips both 
 * multiline and single line comments, as well as trailing spaces.
 * 
 * @ingroup shader
 */
class Preprocessor {
public:
	void parse(const string &filename);
	Code getCode() const;
protected:
	bool isInclude(const string &line);
	void load(const string &filename);
	void onInclude(const string &line);
	void onLine(const string &file, int number, string &text, bool &inComment);
	string stripComments(const string &line, bool &inComment);
private:
	set<string> includes;
	string filename;
	Code code;
};

/** @return the lines of the file that are actual code. */
inline Code Preprocessor::getCode() const {return code;}


#endif
