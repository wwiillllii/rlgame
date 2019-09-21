#pragma once

#include <string>

#ifdef __linux__
	#include <dlfcn.h>
	using native_module_t = void *;
#else
	#error Unsupported OS! (Or you are not compiling with gcc).
#endif

class LoadedModule{
public:
	LoadedModule(std::string path);
	~LoadedModule();

	bool isLoaded() const;
	std::string getPath() const;

private:
	native_module_t handle;
	std::string path;
};
