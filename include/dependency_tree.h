#pragma once

#include <string>
#include <vector>
#include <iterator>

#include "module.h"
#include "loaded_module.h"

class DependencyTree{
public:
	using ModuleLoadOrderInfoList = std::vector<LoadedModule *>;
	using ModuleLoadOrderInfoIterator = ModuleLoadOrderInfoList::const_iterator;

	DependencyTree();
	~DependencyTree();

	void addModule(LoadedModule * mod);
	ModuleLoadOrderInfoIterator cbegin() noexcept;
	ModuleLoadOrderInfoIterator cend() noexcept;

private:
	void sort();

	ModuleLoadOrderInfoList modules;
	mutable unsigned int iterators;
	bool sorted;
};

