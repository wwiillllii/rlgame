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
	size_t size() const noexcept;
	ModuleLoadOrderInfoIterator begin() noexcept;
	ModuleLoadOrderInfoIterator end() noexcept;

private:
	void sort();

	ModuleLoadOrderInfoList modules;
	mutable unsigned int iterators;
	bool sorted;
};

