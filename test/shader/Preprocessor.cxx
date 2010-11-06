/*
 * Preprocessor.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "Preprocessor.hpp"

/** Unit test for Preprocessor. */
class PreprocessorTest {
public:
	void testParse();
};

/** Test a file can be parsed correctly. */
void PreprocessorTest::testParse() {
	
	Preprocessor pp;
	Code code;
	Code::iterator it;
	int i;
	string filename = "test/shader/basic.frag";
	int numbers[6] = {1, 4, 7, 11, 13, 14};
	string lines[6] = {"#version 130\n",
	                   "uniform vec4 Color = vec4(1.0);\n",
	                   "out vec4 FragColor;\n",
	                   "void main() {\n",
	                   "    FragColor = Color;\n",
	                   "}\n"};
	
	cout << "PreprocessorTest::testParse" << endl;
	
	pp.parse(filename);
	code = pp.getCode();
	for (it=code.begin(); it!=code.end(); ++it) {
		i = distance(code.begin(), it);
		assert(it->filename == filename);
		assert(it->number == numbers[i]);
		assert(it->text == lines[i]);
	}
	
	cout << "PASSED" << endl;
}

int main(int argc, char *argv[]) {
	
	PreprocessorTest test;
	
	test.testParse();
	cout << "ALL TESTS PASSED" << endl;
	return 0;
}

