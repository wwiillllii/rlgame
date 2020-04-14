#include <algorithm>
#include <string.h>

#include "loaded_module.h"
#include "rlexception.h"

#ifdef __linux__

using API_getInfo_t = const module_info_t* (*)();

LoadedModule::LoadedModule(std::string path) :
	handle(nullptr),
	path(path)
{
	dlerror();
	this->handle = dlopen(this->path.c_str(), RTLD_LAZY);
	char * error = dlerror();
	if (error != nullptr) throw RLException(
		"Failed to load module " + path + "\n",
		std::string(error) + "\n",
		"LoadedModule::LoadedModule(std::string path)\n"
	);
}

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

void * LoadedModule::getFunction(std::string name) const{
	auto it = this->functions.find(name);
	if (it != this->functions.end())
		return it->second;

	dlerror();
	void * function = dlsym(this->handle, "API_getInfo");
	char * error = dlerror();
	if(error != nullptr) throw RLException(
		"Failed to get function " + name + " from module " + this->path + "\n",
		std::string(error) + "\n",
		"LoadedModule::getFunction(std::string name)\n"
	);

	this->functions[name] = function;
	return function;
}

#endif 


const module_info_t* LoadedModule::getInfo() const{
	API_getInfo_t API_getInfo = (API_getInfo_t)this->getFunction("API_getInfo");
	return API_getInfo();
}

std::string LoadedModule::getName() const{
	return std::string(getInfo()->module_name);
}

uint32_t LoadedModule::getAPIVersion() const{
	return getInfo()->api_version;
}

size_t count_dependencies(module_dependency_t * dependencies){
	module_dependency_t * end = dependencies;
	while (end->module_name != nullptr) end++;
	return end - dependencies;
}

bool LoadedModule::areDependenciesSatisfied(
	std::vector<LoadedModule *>::iterator start,
	std::vector<LoadedModule *>::iterator end
){
	module_dependency_t * dependencies = getInfo()->dependencies;
	std::vector<module_dependency_t> unmet_dependencies = std::vector<module_dependency_t>(
		dependencies,
		dependencies + count_dependencies(dependencies)
	);

	while (start != end){
		decltype(unmet_dependencies)::iterator it = std::find_if(
			unmet_dependencies.begin(),
			unmet_dependencies.end(),
			[&start](const module_dependency_t& tested){
				return	((*start)->getName() == tested.module_name) &&
						(tested.api_version <= (*start)->getAPIVersion());
			}
		);
		if (it != unmet_dependencies.end()) unmet_dependencies.erase(it);
		start++;
	}

	return unmet_dependencies.empty();
}