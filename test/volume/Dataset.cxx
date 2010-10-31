/*
 * Dataset.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include <cstring>
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "Dataset.hpp"
#define DATASETTEST_FILENAME "textures/bunny128.vlb"


/** @brief Utility for viewing a dataset. */
class DatasetViewer : public CanvasListener {
public:
	DatasetViewer(Dataset *dataset);
	void goToNext(Canvas &canvas);
	void goToPrevious(Canvas &canvas);
	void load();
	virtual void onCanvasInitEvent(Canvas &canvas) {}
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas);
	virtual void onCanvasDragEvent(Canvas &canvas) {}
	void setDataset(Dataset *dataset);
private:
	Dataset *dataset;
	GLenum type;
	int slice, width, height, depth;
};

/** Creates a new %DatasetViewer. */
DatasetViewer::DatasetViewer(Dataset *dataset) {
	
	this->dataset = dataset;
	this->type = dataset->getType();
	this->slice = 0;
	this->width = dataset->getWidth();
	this->height = dataset->getHeight();
	this->depth = dataset->getDepth();
}

/** Shows the next slice in the dataset. */
void DatasetViewer::goToNext(Canvas &canvas) {
	
	if (slice == dataset->getDepth()-1)
		slice = -1;
	++slice;
	canvas.refresh();
}

/** Shows the previous slice in the dataset. */
void DatasetViewer::goToPrevious(Canvas &canvas) {
	
	if (slice == 0)
		slice = dataset->getDepth();
	--slice;
	canvas.refresh();
}

/** Prints the value in the volume under the cursor. */
void DatasetViewer::onCanvasButtonEvent(Canvas &canvas) {
	
	// Ignore down state
	if (canvas.getState().combo.action == TOOLKIT_DOWN) {
		return;
	}
	
	// Standard buttons
	if (canvas.getState().combo.trigger == TOOLKIT_LEFT_BUTTON) {
		Index index((height-(canvas.getState().y)), (canvas.getState().x), slice);
		switch (type) {
		case GL_UNSIGNED_BYTE:
			cout << (int)(dataset->getAsByte(index)) << endl;
			break;
		case GL_SHORT:
			cout << dataset->getAsShort(index) << endl;
			break;
		case GL_UNSIGNED_SHORT:
			cout << dataset->getAsUnsignedShort(index) << endl;
			break;
		case GL_FLOAT:
			cout << dataset->getAsFloat(index) << endl;
			break;
		}
	}
	
	// Wheel
	else if (canvas.getState().combo.trigger == TOOLKIT_WHEEL_UP) {
		goToNext(canvas);
	} else if (canvas.getState().combo.trigger == TOOLKIT_WHEEL_DOWN) {
		goToPrevious(canvas);
	}
}

/** Draws a slice to the screen. */
void DatasetViewer::onCanvasDisplayEvent(Canvas &canvas) {
	
	ostringstream stream;
	char *data;
	
	// Clear
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Slice index
	stream << slice;
	canvas.write(stream.str());
	
	// Reset raster position
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2f(-1.0, -1.0);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	// Draw pixels
	data = reinterpret_cast<char*>(dataset->getData());
	data += slice * width * height * dataset->getBlock();
	glDrawPixels(width, height, GL_LUMINANCE, dataset->getType(), data);
}

/** Changes the slice. */
void DatasetViewer::onCanvasKeyEvent(Canvas &canvas) {
	
	switch (canvas.getState().combo.trigger) {
	case TOOLKIT_KEY_UP:
	case TOOLKIT_KEY_RIGHT:
		goToNext(canvas);
		break;
	case TOOLKIT_KEY_DOWN:
	case TOOLKIT_KEY_LEFT:
		goToPrevious(canvas);
		break;
	}
}

/** Test for Dataset. */
class DatasetTest {
public:
	void setUp();
	void tearDown();
	void testDisplay();
private:
	Dataset *dataset;
};

/** Initialize the fixture. */
void DatasetTest::setUp() {

	dataset = new Dataset(DATASETTEST_FILENAME);
	dataset->load();
	dataset->print();
}

/** Cleans up the test fixture. */
void DatasetTest::tearDown() {
	
	delete dataset;
}

/** Tests the dataset can be viewed. */
void DatasetTest::testDisplay() {
	
	Window *window;
	Canvas *canvas;
	DatasetViewer *viewer;
	
	// Initialize
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas(
			dataset->getWidth(),
			dataset->getHeight());
	viewer = new DatasetViewer(dataset);
	
	// Pack window
	canvas->addListener(viewer);
	window->setTitle(dataset->getFilename());
	window->add(canvas);
	window->show();
	
	// Run
	window->run();
	delete window;
	delete canvas;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	DatasetTest test;
	
	test.setUp();
	test.testDisplay();
	test.tearDown();
}

