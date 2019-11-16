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
	Loader & operator=(Loader & other) = delete;
	Loader & operator=(Loader && other) = delete;
	
	void loadModule(std::string path);
	void loadFromDir(std::string dir_path, size_t recursion_level = 0);
	void runModules();
	size_t loadedModuleCount() const;

private:
	void modulesGetDependencies();
	void modulesInitSelf();
	void modulesInitOthers();
	void modulesInitFinish();

	std::vector<LoadedModule*> loaded_modules;
};
