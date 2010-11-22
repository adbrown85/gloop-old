/*
 * Preprocessor.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include "../Test.h"
#include "Preprocessor.hpp"

/** Unit test for Preprocessor. */
class PreprocessorTest : public Test {
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
	
	pp.parse(filename);
	code = pp.getCode();
	for (it=code.begin(); it!=code.end(); ++it) {
		i = distance(code.begin(), it);
		assert(it->filename == filename);
		assert(it->number == numbers[i]);
		assert(it->text == lines[i]);
	}
}

#define HARNESS PreprocessorTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testParse)
RUN_TESTS

