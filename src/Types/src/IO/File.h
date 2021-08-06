
#pragma once

#include "Strings/Strings.h"

class File {

public:

	char* buff;
	int size;

	File();
	File(const Str& path);

	void load(const Str& path);
	void unload();

	~File();
};