#pragma once

#include <stdint.h>

typedef struct{
	char * module_name;
	uint32_t api_version;
} module_dependency_t;

typedef struct{
	char * module_name;
	uint32_t api_version;
	uint32_t module_version;
	module_dependancy_t * dependencies;
} module_info_t;
