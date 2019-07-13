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
	
	LoadedModule & operator=(LoadedModule & other) = delete;
	LoadedModule & operator=(LoadedModule && other) = delete;
	LoadedModule(LoadedModule & other) = delete;
	LoadedModule(LoadedModule && other) = delete;
	
	bool isLoaded() const;
	std::string getPath() const;

private:
	native_module_t handle;
	std::string path;
};
