#include "loader.h"
#include "directory.h"

#ifdef __linux__

#include <sys/types.h>
#include <dirent.h>

Loader::Loader() :
	loaded_modules()
{}

Loader::~Loader(){}

void Loader::loadFromDir(std::string dir_path){

}

size_t Loader::loadedModuleCount() const{
	return this->loaded_module.size();
}

#else
#error Unsupported OS! (Or you are not compiling with gcc).
#endif
