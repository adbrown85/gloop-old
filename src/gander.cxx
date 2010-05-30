/*
 * gander.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "gander.hxx"


/** Creates an instance of the application. */
Gander::Gander(int argc, char *argv[]) {
	
	this->argc = argc;
	this->argv = argv;
	this->display = NULL;
	this->delegate = NULL;
	this->scene = NULL;
	this->canvas = NULL;
}


Gander::~Gander() {
	
	if (display != NULL)
		delete display;
	if (delegate != NULL)
		delete delegate;
	if (scene != NULL)
		delete scene;
	if (canvas != NULL)
		delete canvas;
}


void Gander::banner() {
	
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Gander" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


void Gander::onCompile() {
	
#ifdef HAVE_GTK
	Gtk::Window window;
	
	// Create widgets
	Gtk::GL::init(argc, argv);
	canvas = new CanvasGTK();
	
	// Pack
	window.add(*((CanvasGTK*)canvas));
	window.show_all();
#endif
	
	// Do setup
	canvas->primeStart();
	prime();
	canvas->primeFinish();
}


void Gander::onConvert() {
	
	DatasetWriter writer;
	
	writer.setInput(inFilename);
	writer.setOutput(outFilename);
	if (!parameter.empty())
		writer.setJump(atoi(parameter.c_str()));
	writer.write();
}


/** Starts the display for a scene.
 * 
 * @note Controls are not deleted.
 */
void Gander::onDisplay() {
	
#ifdef HAVE_GTK
	Gtk::Window window;
	Gtk::HBox hBox;
	Gtk::VBox vBox;
	Inspector inspector;
	LogBook logBook;
	
	// Create widgets
	Gtk::GL::init(argc, argv);
	canvas = new CanvasGTK();
	window.set_title(title);
	
	// Pack
	vBox.pack_start(*((CanvasGTK*)canvas), Gtk::PACK_SHRINK);
	vBox.pack_start(logBook);
	hBox.pack_start(inspector);
	hBox.pack_start(vBox, Gtk::PACK_SHRINK);
	window.add(hBox);
	window.show_all();
	
	// Prime the canvas
	canvas->primeStart();
	prime();
	canvas->primeFinish();
	
	// Finalize widgets
	inspector.setScene(scene);
	inspector.setCanvas(canvas);
	inspector.update();
	
	// Run
	Gtk::Main::run(window);
#endif
}


void Gander::onHeader() {
	
	DatasetHeader header(inFilename);
	
	header.print();
}


void Gander::onHistogram() {
	
	Dataset dataset(inFilename);
	DatasetAnalyzer analyzer;
	clock_t ticks;
	
	dataset.load(true);
	analyzer.setDataset(&dataset);
	cout << "Computing histogram..." << endl;
	ticks = clock();
	analyzer.printHistogram();
	cout << (double)(clock() - ticks) / CLOCKS_PER_SEC << "s" << endl;
}


void Gander::onPreprocess() {
	
	Preprocessor pp(inFilename);
	
	pp.start();
	pp.printLines();
}


void Gander::onRange() {
	
	Dataset dataset(inFilename);
	DatasetAnalyzer analyzer;
	clock_t ticks;
	
	dataset.load(true);
	analyzer.setDataset(&dataset);
	cout << "Computing actual range..." << endl;
	ticks = clock();
	analyzer.printRange();
	cout << (double)(clock() - ticks) / CLOCKS_PER_SEC << "s" << endl;
}


void Gander::onSlices() {
	
	// Load the dataset
	Dataset dataset(inFilename);
	dataset.load();
	dataset.print();
	
	// Initialize window
#ifdef HAVE_GTK
	Gtk::GL::init(argc, argv);
	Gtk::Window window;
	CanvasGTK canvas(dataset.getWidth(), dataset.getHeight());
#endif
	
	// Create the viewer
	DatasetViewer viewer;
	viewer.setCanvas(&canvas);
	viewer.setDataset(&dataset);
	viewer.load();
	
	// Pack and run window
#ifdef HAVE_GTK
	window.set_title(dataset.getFilename());
	window.add(canvas);
	window.show_all_children();
	Gtk::Main::run(window);
#endif
}


/** Parses the command line arguments. */
void Gander::parse() {
	
	// Handle arguments
	if (argc == 2) {
		inFilename = argv[1];
	} else if (argc == 3) {
		option = argv[1];
		inFilename = argv[2];
	} else if (argc == 4) {
		option = argv[1];
		inFilename = argv[2];
		outFilename = argv[3];
	} else if (argc == 5) {
		option = argv[1];
		parameter = argv[2];
		inFilename = argv[3];
		outFilename = argv[4];
	} else {
		usage();
		exit(1);
	}
}


/** Loads GLEW, opens the scene, and creates the display. */
void Gander::prime() {
	
	GLenum err;
	
	// Load GLEW
	err = glewInit();
	if (err != GLEW_OK) {
		throw Exception("[Gander] Could not initialize GLEW");
	}
	
	// Open scene
	scene = new Scene();
	delegate = new Delegate(scene, canvas);
	delegate->run(Command::OPEN, inFilename);
	
	// Add display and controls
	display = new Display(delegate);
	display->add(new Keyboard(delegate));
	display->add(new Mouse(delegate));
}


/** Starts the actions. */
void Gander::start() {
	
	// Initialize
	parse();
	title = string("Gander [") + inFilename + "]";
	
	// Handle option
	if (option == "--preprocess") {
		onPreprocess();
	} else if (option == "--slices") {
		onSlices();
	} else if (option == "--header") {
		onHeader();
	} else if (option == "--compile") {
		onCompile();
	} else if (option == "--convert") {
		onConvert();
	} else if (option == "--range") {
		onRange();
	} else if (option == "--histogram") {
		onHistogram();
	} else {
		banner();
		onDisplay();
		banner();
	}
}


/** Prints a usage message. */
void Gander::usage() {
	
	cerr << "Usage: " << argv[0] << " [OPTION] INPUT [OUTPUT]" << endl;
	cerr << endl;
	cerr << "Options: " << endl;
	cerr << "  --display        Display a scene (the default)" << endl;
	cerr << "  --compile        Compile but do not display scene" << endl;
	cerr << "  --preprocess     Preprocess GLSL file" << endl;
	cerr << "  --slices         View the slices of dataset" << endl;
	cerr << "  --header         Print header of volume file" << endl;
	cerr << "  --range          Find actual high and low of dataset" << endl;
	cerr << "  --histogram      Show distribution in dataset" << endl;
	cerr << "  --convert [i]    Convert volume taking every i'th voxel" << endl;
}


int main(int argc, char *argv[]) {
	
#ifdef HAVE_GTK
	Gtk::Main kit(argc, argv);
#endif
	Gander gander(argc, argv);
	
	try {
		gander.start();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	return 0;
}

