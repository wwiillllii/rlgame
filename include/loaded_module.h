#pragma once

#include <string>

#ifdef __linux__
	#include <dlfcn.h>
	using native_module_t = void *;
#else
	#error Unsupported OS! (Or you are not compiling with gcc).
#endif

#include "module.h"

class LoadedModule{
public:
	LoadedModule(std::string path);
	~LoadedModule();

	bool isLoaded() const;
	std::string getPath() const;

	const module_info_t* getInfo(Loader & loader);
	bool initSelf(Loader & loader);
	bool initOthers(Loader & loader);
	bool finalizeOthers(Loader & loader);
	bool finalizeSelf(Loader & loader);

private:
	native_module_t handle;
	std::string path;
};
