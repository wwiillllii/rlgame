#include "loader.h"
#include "directory.h"

#ifdef __linux__

#include <sys/types.h>
#include <dirent.h>

Loader::Loader() :
	loaded_modules()
{}

Loader::~Loader(){}

void Loader::loadModule(std::string path){
	loaded_modules.push_back(path);
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

#else
#error Unsupported OS! (Or you are not compiling with gcc).
#endif
