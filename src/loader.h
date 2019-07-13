#pragma once

#include <string>
#include <vector>

#include "loaded_module.h"

class Loader{
public:
	Loader();
	~Loader();
	
	Loader(Loader & other) = delete;
	Loader(Loader && other) = delete;
	operator=(Loader & other) = delete;
	operator=(Loader && other) = delete;
	
	void loadFromDir(std::string dir_path);
	size_t loadedModuleCount() const;

private:
	vector<LoadedModule> loaded_modules;
}
