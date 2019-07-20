#include "loaded_module.h"

#ifdef __linux__

LoadedModule::LoadedModule(std::string path) :
	handle(dlopen(path.c_str(), RTLD_GLOBAL)),
	path(path)
{}

LoadedModule::~LoadedModule(){
	if (this->handle != nullptr){
		dlclose(this->handle);
		this->handle = nullptr;
	}
}

bool LoadedModule::isLoaded() const{
	return this->handle != nullptr;
}

std::string LoadedModule::getPath() const{
	return this->path;
}

#endif 
