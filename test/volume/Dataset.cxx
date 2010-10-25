/*
 * Dataset.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include <glawt/Toolkit.hpp>
#include <glawt/CanvasFactory.hpp>
#include <glawt/WindowFactory.hpp>
#include "Dataset.hpp"


/** @brief Utility for viewing a dataset. */
class DatasetViewer : public CanvasListener {
public:
	void goToNext();
	void goToPrevious();
	void load();
	void onCanvasEvent(const CanvasEvent &event);
	void onCanvasEventButton(const CanvasEvent &event);
	void onCanvasEventDisplay(const CanvasEvent &event);
	void onCanvasEventKey(const CanvasEvent &event);
	void setCanvas(Canvas *canvas);
	void setDataset(Dataset *dataset);
private:
	Dataset *dataset;
	GLenum type;
	int slice, width, height, depth;
	Canvas *canvas;
};
inline void DatasetViewer::setCanvas(Canvas *c) {canvas = c;}
inline void DatasetViewer::setDataset(Dataset *d) {dataset = d;}

/** Shows the next slice in the dataset. */
void DatasetViewer::goToNext() {
	
	if (slice == dataset->getDepth()-1)
		slice = -1;
	++slice;
	canvas->refresh();
}

/** Shows the previous slice in the dataset. */
void DatasetViewer::goToPrevious() {
	
	if (slice == 0)
		slice = dataset->getDepth();
	--slice;
	canvas->refresh();
}

/** Handles the incoming canvas event. */
void DatasetViewer::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::BUTTON :
		onCanvasEventButton(event);
		break;
	case CanvasEvent::DISPLAY :
		onCanvasEventDisplay(event);
		break;
	case CanvasEvent::KEY :
		onCanvasEventKey(event);
		break;
	}
}

/** Prints the value in the volume under the cursor. */
void DatasetViewer::onCanvasEventButton(const CanvasEvent &event) {
	
	// Ignore down state
	if (event.state.combo.action == TOOLKIT_DOWN) {
		return;
	}
	
	// Standard buttons
	if (event.state.combo.trigger == TOOLKIT_LEFT_BUTTON) {
		Index index((height-(event.state.y)), (event.state.x), slice);
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
	else if (event.state.combo.trigger == TOOLKIT_WHEEL_UP) {
		goToNext();
	} else if (event.state.combo.trigger == TOOLKIT_WHEEL_DOWN) {
		goToPrevious();
	}
}

/** Draws a slice to the screen. */
void DatasetViewer::onCanvasEventDisplay(const CanvasEvent &event) {
	
	ostringstream stream;
	char *data;
	
	// Clear
	canvas->clear();
	
	// Slice index
	stream << slice;
	canvas->write(stream.str());
	
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
	
	// Flush
	canvas->flush();
}

/** Changes the slice. */
void DatasetViewer::onCanvasEventKey(const CanvasEvent &event) {
	
	switch(event.state.combo.trigger) {
	case TOOLKIT_KEY_UP:
	case TOOLKIT_KEY_RIGHT:
		goToNext();
		break;
	case TOOLKIT_KEY_DOWN:
	case TOOLKIT_KEY_LEFT:
		goToPrevious();
		break;
	}
}

/** Copies attributes from the dataset and adds listeners to the canvas. */
void DatasetViewer::load() {
	
	// Set fields
	this->width = dataset->getWidth();
	this->height = dataset->getHeight();
	this->depth = dataset->getDepth();
	this->type = dataset->getType();
	this->slice = 0;
	
	// Create the canvas
	canvas->addListener(this, CanvasEvent::DISPLAY);
	canvas->addListener(this, CanvasEvent::BUTTON);
	canvas->addListener(this, CanvasEvent::KEY);
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		filename = "../../textures/bunny128.vlb";
	} else if (argc == 2) {
		filename = argv[1];
	} else {
		cerr << "Usage: " << argv[0] << " [<filename>]" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	Window *window;
	Canvas *canvas;
	
	try {
		
		// Set up the dataset
		Dataset dataset(filename);
		dataset.load();
		dataset.print();
		
		// Initialize
		Toolkit kit(argc, argv);
		
		// Window and canvas
		window = WindowFactory::create();
		canvas = CanvasFactory::create(dataset.getWidth(), dataset.getHeight());
		
		// Create the viewer
		DatasetViewer viewer;
		viewer.setCanvas(canvas);
		viewer.setDataset(&dataset);
		viewer.load();
		
		// Pack window
		window->setTitle(dataset.getFilename());
		window->add(canvas);
		window->show();
		
		// Run
		window->run();
		delete window;
		delete canvas;
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

