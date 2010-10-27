/*
 * BasicException.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BASICEXCEPTION_HPP
#define BASICEXCEPTION_HPP
#include "common.h"
#include <exception>
using namespace std;


/** @brief %BasicException backed by a stringstream for easy message building.
 * @ingroup system
 */
class BasicException : public exception {
public:
	BasicException() {};
	BasicException(const BasicException &e);
	BasicException(const string &message);
	~BasicException() throw() {}
	string getMessage() const;
	const char* what() const throw();
	ostream& operator<<(const string &message);
	ostream& operator<<(const BasicException &e);
	friend ostream& operator<<(ostream& stream, BasicException &e);
private:
	ostringstream buffer;
};


#endif
