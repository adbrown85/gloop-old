/*
 * BitmapImageReader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BitmapImageReader.hpp"

/** Creates a new image reader. */
BitmapImageReader::BitmapImageReader() {
	
	pixels = NULL;
}

/** Destroys the image reader. */
BitmapImageReader::~BitmapImageReader() {
	
	if (pixels != NULL) {
		delete[] pixels;
	}
}

/** Read image in @e filename into memory.
 * 
 * @throw ImageException from open()
 * @throw ImageException from readFileHeader()
 * @throw ImageException from readInfoHeader()
 * @throw ImageException from readPixels()
 * 
 * @see getFormat()
 * @see getPixels()
 * @see getSize()
 * @see getWidth()
 * @see getHeight()
 */
void BitmapImageReader::read(const string &filename) {
	
	try {
		open(filename);
		readFileHeader();
		readInfoHeader();
		readPixels();
		close();
	} catch (BasicException &e) {
		close();
		throw e;
	}
}

/** Copy pixel data to an array of bytes.
 * 
 * @throw ImageException if array is NULL
 * @throw ImageException if size is not equal to the image's size
 */
void BitmapImageReader::toArray(char *array, size_t size) {
	
	if (array == NULL) {
		ImageException e;
		e << "[BitmapImageReader] Array is NULL!";
		throw e;
	}
	
	if (size != getSize()) {
		ImageException e;
		e << "[BitmapImageReader] Array is not the right size!";
		throw e;
	}
	
	memcpy(array, pixels, size);
}

//--------------------------------------------------------
// Helpers
//

/** Opens the file.
 * 
 * @throw ImageException if file cannot be read
 */
void BitmapImageReader::open(const string &filename) {
	
	file.open(filename.c_str(), ios_base::binary);
	if (!file) {
		ImageException e;
		e << "[BitmapImageReader] Image '" << filename << "' does not exist!";
		throw e;
	}
}

/** Closes the file. */
void BitmapImageReader::close() {
	
	file.close();
}

/** Reads just the file header section. */
void BitmapImageReader::readFileHeader() {
	
	file.read((char*)&fileHeader.bfType, 2);
	file.read((char*)&fileHeader.bfSize, 4);
	file.read((char*)&fileHeader.bfReserved1, 2);
	file.read((char*)&fileHeader.bfReserved2, 2);
	file.read((char*)&fileHeader.bfOffBits, 4);
	
	if (!isValidFileHeader()) {
		ImageException e;
		e << "[BitmapImageReader] Not a valid bitmap file header!";
		throw e;
	}
}

/** Reads just the info header section.
 * 
 * @throw ImageException if not a valid bitmap info header 
 * @throw ImageException if bitmap is compressed
 * @throw ImageException if bitmap is not 24-bit
 */
void BitmapImageReader::readInfoHeader() {
	
	file.read((char*)&infoHeader.biSize, 4);
	file.read((char*)&infoHeader.biWidth, 4);
	file.read((char*)&infoHeader.biHeight, 4);
	file.read((char*)&infoHeader.biPlanes, 2);
	file.read((char*)&infoHeader.biBitCount, 2);
	file.read((char*)&infoHeader.biCompression, 4);
	file.read((char*)&infoHeader.biSizeImage, 4);
	file.read((char*)&infoHeader.biXPelsPerMeter, 4);
	file.read((char*)&infoHeader.biYPelsPerMeter, 4);
	file.read((char*)&infoHeader.biClrUsed, 4);
	file.read((char*)&infoHeader.biClrImportant, 4);
	
	if (!isValidInfoHeader()) {
		ImageException e;
		e << "[BitmapImageReader] Not a valid bitmap info header!";
		throw e;
	}
	
	if (isCompressed()) {
		ImageException e;
		e << "[BitmapImageReader] Only supports uncompressed data.";
		throw e;
	}
	
	if (!is24Bit()) {
		ImageException e;
		e << "[BitmapImageReader] Only supports 24-bit data.";
		throw e;
	}
}

/** Read the pixel data into memory.
 * 
 * @throw ImageException if improper amount of pixels were read 
 */
void BitmapImageReader::readPixels() {
	
	size_t size = getSize();
	
	pixels = new char[size];
	file.read(pixels, size);
	if (file.gcount() != size) {
		ImageException e;
		e << "[BitmapImageReader] All pixels could not be read!";
		throw e;
	}
}

//--------------------------------------------------------
// Getters and setters
//

/** @return Number of bytes that row length should be multiples of. */
GLuint BitmapImageReader::getAlignment() {
	return 4;
}

/** @return Format of the image (GL_BGR). */
GLenum BitmapImageReader::getFormat() {
	return GL_BGR;
}

/** @return Total number of bytes required to hold the image. */
GLuint BitmapImageReader::getSize() {
	return infoHeader.biSizeImage;
}

/** @return Number of pixels in the X direction. */
GLuint BitmapImageReader::getWidth() {
	return infoHeader.biWidth;
}

/** @return Number of pixels in the Y direction. */
GLuint BitmapImageReader::getHeight() {
	return infoHeader.biHeight;
}

//--------------------------------------------------------
// Utilities
//

/** @return True if the file header is valid. */
bool BitmapImageReader::isValidFileHeader() {
	return fileHeader.bfType[0] == 'B' 
			&& fileHeader.bfType[1] == 'M'
			&& fileHeader.bfReserved1 == 0
			&& fileHeader.bfReserved2 == 0;
}

/** @return True if the info header is valid. */
bool BitmapImageReader::isValidInfoHeader() {
	return infoHeader.biSize == 40
			&& infoHeader.biWidth > 0
			&& infoHeader.biHeight > 0
			&& infoHeader.biPlanes == 1;
}

/** @return True if any info header fields indicate the data is compressed. */
bool BitmapImageReader::isCompressed() {
	return infoHeader.biCompression != 0;
}

/** @return True if info header fields indicate the data is 24-bit. */
bool BitmapImageReader::is24Bit() {
	return infoHeader.biBitCount == 24
			&& infoHeader.biClrUsed == 0
			&& infoHeader.biClrImportant == 0;
}

