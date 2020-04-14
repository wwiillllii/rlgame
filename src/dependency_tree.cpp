#include <algorithm>
#include <vector>
#include <string.h>
#include <iostream> // TODO: Remove

#include "dependency_tree.h"
#include "rlexception.h"


//------------------------------ Iterator Stuff --------------------------------


using ModuleLoadOrderInfoIterator = DependencyTree::ModuleLoadOrderInfoIterator;
using ModuleLoadOrderInfoList = DependencyTree::ModuleLoadOrderInfoList;

class CounterLock{
public:
	CounterLock(unsigned int * counter_ptr) : counter_ptr(counter_ptr){
		*counter_ptr += 1;
	}

	~CounterLock() noexcept(false){
		if (counter_ptr == nullptr) throw RLException(
			"Lowering counter failed\n",
			"Pointer to counter not set\n",
			"CounterLock::~CounterLock()\n"
		);
		if (*counter_ptr == 0) throw RLException(
			"Lowering counter failed\n",
			"Counter is already zero\n",
			"CounterLock::~CounterLock()\n"
		);
		*counter_ptr -= 1;
	}

private:
	unsigned int * counter_ptr;
};

class DependencyTreeIterator : public ModuleLoadOrderInfoIterator{
public:
	DependencyTreeIterator(
		ModuleLoadOrderInfoIterator base,
		unsigned int * iterator_count_ptr
	) :
		ModuleLoadOrderInfoIterator(base),
		lock(CounterLock(iterator_count_ptr))
	{}

	LoadedModule * operator*(){
		return this->ModuleLoadOrderInfoIterator::operator*();
	}

private:
	CounterLock lock;
};


//- ---------------------- DependencyTree Implementation -----------------------


DependencyTree::DependencyTree() : 
	iterators(0),
	sorted(true)
{}

DependencyTree::~DependencyTree(){}

void DependencyTree::addModule(LoadedModule * module){
	sorted = false;
	this->modules.push_back(module);
}

ModuleLoadOrderInfoIterator DependencyTree::cbegin() noexcept{
	sort();
	return DependencyTreeIterator(
		this->modules.cbegin(),
		&this->iterators
	);
}

ModuleLoadOrderInfoIterator DependencyTree::cend() noexcept{
	sort();
	return DependencyTreeIterator(
		this->modules.cend(),
		&this->iterators
	);
}

void DependencyTree::sort(){
	if (sorted) return;

	CounterLock lock(&this->iterators);
	auto buffer_start = modules.begin();
	auto buffer_end = modules.end();
	LoadedModule * tmp;
	std::string unloadable_modules;

	std::cout << "Sorting modules..." << std::endl;
	// For all positions in [start, end)
	for (auto next_position = buffer_start; next_position != buffer_end; next_position++){
		unloadable_modules = "";
		// Find a candidate from [position, end)
		auto next_candidate = next_position;
		for (;next_candidate != buffer_end; next_candidate++){
			unloadable_modules += "\t";
			unloadable_modules += (*next_candidate)->getName();
			unloadable_modules += "\n";
			// Whose dependencies are met in [start, position)
			if ((*next_candidate)->areDependenciesSatisfied(buffer_start, next_position)){
				// And the insert the candidate into the position.
				std::cout << "Next module: " << (*next_candidate)->getName() << std::endl;
				tmp = *next_candidate;
				*next_candidate = *next_position;
				*next_position = tmp;
				break;
			}
		}
		// If no valid candidate was found for the position, the sorting failed.
		if (next_candidate == buffer_end){
			throw RLException(
				"Sorting module load order failed\n",
				"Some modules have unmet dependencies:\n" + unloadable_modules,
				"DependencyTree::sort()\n"
			);
		}
	}

	std::cout << "Done sorting!" << std::endl;
	sorted = true;
}

