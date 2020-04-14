#pragma once

#include <stdint.h>

#define MODULE_NAME_MAX_LENGTH 255

typedef struct{
	const char * module_name;
	uint32_t api_version;
} module_dependency_t;

typedef struct{
	const char * module_name;
	uint32_t api_version;
	uint32_t module_version;
	module_dependency_t * dependencies;
} module_info_t;

