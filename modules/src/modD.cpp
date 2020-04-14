#include <iostream>

#include "module.h"

static module_dependency_t deps[]{
	{"modB", 0},
	{"modF", 0},
	{nullptr, 0},
};

static const module_info_t info = {
	.module_name = "modD",
	.api_version = 0,
	.module_version = 0,
	.dependencies = deps,
};

extern "C" const module_info_t * API_getInfo(){
	std::cout << "modD::API_getInfo called!" << std::endl;
	return &info;
}

