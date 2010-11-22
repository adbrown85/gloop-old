/*
 * Runner.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLOOP_RUNNER_H_
#define GLOOP_RUNNER_H_
#include <glawt/Toolkit.hpp>
#include "ErrorChecker.hpp"

typedef HARNESS test_t;
typedef void (HARNESS::*method_t)();

#define START_TESTS \
int main(int argc, char *argv[]) { \
    Toolkit kit(argc, argv); \
    HARNESS test; \
    test.init();

#define ADD_TEST(X) \
    Runner::add(#X, &HARNESS::X);

#define RUN_TESTS \
    Runner::run(test); \
    return 0; \
}

struct TestCase {
	string name;
	method_t method;
};

class Runner {
public:
	static void run(test_t &test);
	static void add(const string &name, method_t method);
private:
	static list<TestCase> testCases;
};
list<TestCase> Runner::testCases;

void Runner::add(const string &name, method_t method) {
	
	TestCase tc;
	
	tc.name = name;
	tc.method = method;
	testCases.push_back(tc);
}

void Runner::run(test_t &test) {
	
	list<TestCase>::iterator it;
	
	for (it=testCases.begin(); it!=testCases.end(); ++it) {
		test.setUp();
		cout << "RUNNING " << it->name << endl;
		try {
			(test.*(it->method))();
		} catch (exception &e) {
			cout << "FAILED!" << endl;
			exit(1);
		}
		ErrorChecker::assertNoError(it->name);
		cout << "PASSED" << endl;
		test.tearDown();
	}
	cout << "ALL TESTS PASSED" << endl;
}

#endif
