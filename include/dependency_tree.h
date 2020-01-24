#pragma once

#include <string>
#include <vector>
#include <iterator>

#include <module.h>

class DependencyTree{
public:
	using ModuleLoadOrderInfo=struct {
		module_info_t* module;
		unsigned int priority;
		bool visited;
	};
	using ModuleLoadOrderInfoList = std::vector<ModuleLoadOrderInfo>;
	using ModuleLoadOrderInfoIterator = ModuleLoadOrderInfoList::const_iterator;

	DependencyTree();
	~DependencyTree();

	void addModule(module_info_t * mod);
	ModuleLoadOrderInfoIterator cbegin() const noexcept;
	ModuleLoadOrderInfoIterator cend() const noexcept;

private:
	void sort();

	std::vector<ModuleLoadOrderInfo> modules;
	mutable unsigned int iterators;
};

