/*
 * Dataset.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gloop_common.h"
#include "../Test.h"
#include "Dataset.hpp"
#define DATASETTEST_FILENAME "test/volume/bunny128.vlb"

/** Test for Dataset. */
class DatasetTest : public Test {
public:
	DatasetTest();
	virtual ~DatasetTest();
	void testDisplay();
// Event handlers
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas);
// Hooks
	virtual int doGetWidth() {return dataset->getWidth();}
	virtual int doGetHeight() {return dataset->getHeight();}
	virtual string doGetTitle() {return dataset->getFilename();}
protected:
	void goToNext(Canvas &canvas);
	void goToPrevious(Canvas &canvas);
private:
	Dataset *dataset;
	int slice;
};

/** Initialize the fixture. */
DatasetTest::DatasetTest() {
	
	dataset = new Dataset(DATASETTEST_FILENAME);
	dataset->load();
	slice = 0;
}

/** Cleans up the test fixture. */
DatasetTest::~DatasetTest() {
	
	delete dataset;
}

/** Shows the next slice in the dataset. */
void DatasetTest::goToNext(Canvas &canvas) {
	
	if (slice == dataset->getDepth()-1)
		slice = -1;
	++slice;
	canvas.refresh();
}

/** Shows the previous slice in the dataset. */
void DatasetTest::goToPrevious(Canvas &canvas) {
	
	if (slice == 0)
		slice = dataset->getDepth();
	--slice;
	canvas.refresh();
}

/** Prints the value in the volume under the cursor. */
void DatasetTest::onCanvasButtonEvent(Canvas &canvas) {
	
	Index index;
	
	// Ignore down state
	if (canvas.getState().combo.action == TOOLKIT_DOWN) {
		return;
	}
	
	// Standard buttons
	if (canvas.getState().combo.trigger == TOOLKIT_LEFT_BUTTON) {
		index.i = dataset->getHeight() - canvas.getState().y;
		index.j = canvas.getState().x;
		index.k = slice;
		switch (dataset->getType()) {
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
void DatasetTest::onCanvasDisplayEvent(Canvas &canvas) {
	
	ostringstream stream;
	char *data;
	int area = dataset->getWidth() * dataset->getHeight();
	
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
	data += slice * area * dataset->getBlock();
	glDrawPixels(
			dataset->getWidth(),
			dataset->getHeight(),
			GL_LUMINANCE,
			dataset->getType(),
			data);
}

/** Changes the slice. */
void DatasetTest::onCanvasKeyEvent(Canvas &canvas) {
	
	Test::onCanvasKeyEvent(canvas);
	
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

/** Tests the dataset can be viewed. */
void DatasetTest::testDisplay() {
	
	runWindow();
}

/* Run the test. */
#define HARNESS DatasetTest
#include "../Runner.h"
START_TESTS
ADD_TEST(testDisplay)
RUN_TESTS
