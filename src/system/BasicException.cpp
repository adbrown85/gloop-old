/*
 * BasicException.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BasicException.hpp"


BasicException::BasicException(const BasicException &e) {
	
	buffer << e.getMessage();
}


BasicException::BasicException(const string &message) {
	
	buffer << message;
}


string BasicException::getMessage() const {
	
	return buffer.str();
}


ostream& BasicException::operator<<(const string &message) {
	
	buffer << message;
	return buffer;
}


ostream& BasicException::operator<<(const BasicException &e) {
	
	buffer << e.getMessage();
	return buffer;
}


ostream& operator<<(ostream &stream, BasicException &e) {
	
	stream << e.buffer.str();
	return stream;
}


const char* BasicException::what() const throw() {
	
	return buffer.str().c_str();
}

