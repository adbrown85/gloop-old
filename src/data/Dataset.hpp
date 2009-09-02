/*
 * Dataset.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef DATASET_HPP
#define DATASET_HPP
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
using namespace std;



/**
 * @brief
 *     Loads and holds volumetric data.
 * @ingroup data
 */
class Dataset {
	
	
	public :
		
		Dataset(const string &filename);
		~Dataset();
		void print() const;
		
		void* getData() const;
		int getDepth() const {return depth;}
		float* getFloatData() const {return floatData;}
		int getHeight() const {return height;}
		short* getShortData() const {return shortData;}
		GLenum getTypeEnum() const {return typeEnum;}
		string getTypeString() const {return typeString;}
		unsigned char* getUByteData() const {return ubyteData;}
		unsigned short* getUShortData() const {return ushortData;}
		int getWidth() const {return width;}
	
	
	private:
		
		unsigned char *ubyteData;
		float *floatData, pitch[3];
		GLenum typeEnum;
		int count, dataOffset, headerOffset;
		int max, min, range[2], size[3];
		int width, height, depth;
		short *shortData;
		unsigned short *ushortData;
		string endian, filename, typeString;
		
		Dataset();
		void checkHeader();
		void initData();
		void initDimensions();
		void initTypeEnum();
		void readData();
		void readDataAsFloat(ifstream &file);
		void readDataAsShort(ifstream &file);
		void readDataAsUByte(ifstream &file);
		void readDataAsUShort(ifstream &file);
		void readHeader();
		void setDimensions(int width,
		                   int height,
		                   int depth);
};


#endif