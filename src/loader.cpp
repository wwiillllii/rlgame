#include <iostream>

#include "loader.h"
#include "directory.h"

#ifdef __linux__

#include <sys/types.h>
#include <dirent.h>

Loader::Loader() :
	loaded_modules()
{}

Loader::~Loader(){
	// TODO: de-init modules (in reverse init order) before deleting them.
	// TODO: or just make modules de-init their dependencies.
	for (LoadedModule * module : loaded_modules)
		delete module;
	loaded_modules.clear();
}

void Loader::loadModule(std::string path){
	loaded_modules.push_back(new LoadedModule(path));
}

void Loader::loadFromDir(std::string dir_path, size_t recursion_level){
	Directory dir(dir_path);
	
	for (auto file : dir.getFiles())
		loadModule(file);
	
	if (recursion_level != 0){
		if (recursion_level != ((unsigned size_t)-1))
			recursion_level--;
		for (auto subdir : dir.getSubdirs())
			loadFromDir(subdir, recursion_level);
	}
}

size_t Loader::loadedModuleCount() const{
	return this->loaded_modules.size();
}

void Loader::runModules(){
	// TODO: implement this function properly.
	for (LoadedModule * module : this->loaded_modules){
		const module_info_t* info = module->getInfo();
		std::cout << info->module_name << std::endl;
	}
}

#else
#error Unsupported OS! (Or you are not compiling with gcc).
#endif
