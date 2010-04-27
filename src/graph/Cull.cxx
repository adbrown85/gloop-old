/*
 * Cull.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cull.hpp"
#include "Tester.hpp"
#include "RenderFactory.hpp"
#include "ShaderFactory.hpp"
#include "ShapeFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		Tester::init(argc, argv);
		Tester::install(new RenderFactory());
		Tester::install(new ShaderFactory());
		Tester::install(new ShapeFactory());
		Tester::open("Cull.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}
