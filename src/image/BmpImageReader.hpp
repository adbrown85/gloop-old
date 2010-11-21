/*
 * BmpImageReader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BMPIMAGEREADER_HPP
#define BMPIMAGEREADER_HPP
#include "gloop_common.h"
#include <fstream>
#include <cstring>
#include "Image.hpp"

/* File header of a bitmap image. */
struct BmpFileHeader {
	char bfType[2];
	GLuint bfSize;
	GLushort bfReserved1;
	GLushort bfReserved2;
	GLuint bfOffBits;
};

/* Information header of a bitmap image. */
struct BmpInfoHeader {
	GLuint biSize;
	GLuint biWidth;
	GLuint biHeight;
	GLushort biPlanes;
	GLushort biBitCount;
	GLuint biCompression;
	GLuint biSizeImage;
	GLuint biXPelsPerMeter;
	GLuint biYPelsPerMeter;
	GLuint biClrUsed;
	GLuint biClrImportant;
};

/** @brief Reads a bitmap image into memory.
 * 
 * @ingroup image
 */
class BmpImageReader : public ImageReader {
public:
	BmpImageReader();
	virtual ~BmpImageReader();
	virtual void read(const string &filename);
	virtual void toArray(char *array, size_t size);
// Getters and setters
	virtual GLuint getAlignment();
	virtual GLenum getFormat();
	virtual GLuint getSize();
	virtual GLuint getWidth();
	virtual GLuint getHeight();
protected:
	virtual void open(const string &filename);
	virtual void close();
	virtual void readFileHeader();
	virtual void readInfoHeader();
	virtual void readPixels();
// Utilities
	virtual bool isValidFileHeader();
	virtual bool isValidInfoHeader();
	virtual bool isCompressed();
	virtual bool is24Bit();
private:
	ifstream file;
	BmpFileHeader fileHeader;
	BmpInfoHeader infoHeader;
	char *pixels;
};

#endif
