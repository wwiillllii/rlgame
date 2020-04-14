#include <iostream>

#include "module.h"

static module_dependency_t deps[]{
	{"modE", 0},
	{"modG", 0},
	{nullptr, 0},
};

static const module_info_t info = {
	.module_name = "modF",
	.api_version = 0,
	.module_version = 0,
	.dependencies = deps,
};

extern "C" const module_info_t * API_getInfo(){
	std::cout << "modF::API_getInfo called!" << std::endl;
	return &info;
}

