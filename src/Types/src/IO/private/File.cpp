
#include "IO/File.h"

#include "Memory/Mem.h"

#include <iostream>
#include <fstream>

void File::load(const Str& path) {

	unload();

	std::ifstream infile(path.str);

	//get length of file
	infile.seekg(0, std::ios::end);
	size_t length = infile.tellg();
	infile.seekg(0, std::ios::beg);

	buff = new char[length];

	//read file
	infile.read(buff, length);
	size = length;
	
	infile.close();
}

void File::unload() {
	if (buff) {
		delete buff;
	}
	size = 0;
}

File::File(const Str& path) {
	load(path);
}

File::File() : buff(0), size(0) {}

File::~File() {
	unload();
}