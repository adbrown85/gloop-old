/*
 * Image.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cassert>
#include <glawt/CanvasGTK.hpp>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "Image.hpp"


/* Fake image for testing. */
class FakeImage : public Image {
public:
	FakeImage(const string &filename) : Image(filename) {}
	virtual GLchar* getData() const {return NULL;}
};

/* Test for Image. */
class ImageTest : public CanvasListener {
public:
	void setUp();
	void testFormat();
	void testGetData();
	void onCanvasInitEvent(Canvas &canvas) {}
	void onCanvasDisplayEvent(Canvas &canvas);
	void onCanvasKeyEvent(Canvas &canvas) {}
	void onCanvasButtonEvent(Canvas &canvas) {}
	void onCanvasDragEvent(Canvas &canvas) {}
private:
	Image *image;
	CanvasGTK *canvas;
	Gtk::Window *window;
};

/* Load the image. */
void ImageTest::setUp() {
	
	cout << "Setting up..." << endl;
	
	// Create image
	image = new FakeImage("../../textures/crate.jpg");
}

/* Makes sure the image determined if it uses alpha or not. */
void ImageTest::testFormat() {
	
	cout << "\nTesting format..." << endl;
	
	// Assert
	switch (image->getFormat()) {
	case GL_RGB:
		cout << "  GL_RGB" << endl;
		break;
	case GL_RGBA:
		cout << "  GL_RGBA" << endl;
		break;
	}
	assert(image->getFormat() == GL_RGB);
}

/* Displays the image in OpenGL. */
void ImageTest::testGetData() {
	
	cout << "\nTesting getData()..." << endl;
	
	// Create canvas
	canvas = new CanvasGTK();
	canvas->addListener(this);
	
	// Pack
	window = new Gtk::Window();
	window->set_title("Image Test");
	window->add(*canvas);
	window->show_all();
	
	// Run
	Gtk::Main::run(*window);
}

/* Handles an incoming canvas display event. */
void ImageTest::onCanvasDisplayEvent(Canvas &canvas) {
	
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glDrawPixels(image->getWidth(),
	             image->getHeight(),
	             image->getFormat(),
	             GL_UNSIGNED_BYTE,
	             image->getData());
}

/* Run the test */
int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	Gtk::GL::init(argc, argv);
	ImageTest test;
	
	test.setUp();
	test.testFormat();
	test.testGetData();
	return 0;
}

