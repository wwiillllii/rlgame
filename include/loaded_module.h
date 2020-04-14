#pragma once

#include <string>
#include <map>
#include <vector>

#include "module.h"

#ifdef __linux__
	#include <dlfcn.h>
	using native_module_t = void *;
#else
	#error Unsupported OS! (Or you are not compiling with gcc).
#endif

class Loader;

class LoadedModule{
public:
	explicit LoadedModule(std::string path);
	~LoadedModule();

	bool isLoaded() const;
	std::string getPath() const;

	const module_info_t* getInfo() const;
	bool initSelf();
	bool initOthers();
	bool finalizeOthers();
	bool finalizeSelf();

	std::string getName() const;
	uint32_t getAPIVersion() const;

	bool areDependenciesSatisfied(
		std::vector<LoadedModule *>::iterator start,
		std::vector<LoadedModule *>::iterator end
	);

private:
	void * getFunction(std::string name) const;

	mutable std::map<std::string, void*> functions;
	native_module_t handle;
	std::string path;
	const module_info_t * info;
};
