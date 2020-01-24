#include "dependency_tree.h"
#include "rlexception.h"


//------------------------------ Iterator Stuff --------------------------------


using ModuleLoadOrderInfoIterator = DependencyTree::ModuleLoadOrderInfoIterator;

class DependencyTreeIterator : public ModuleLoadOrderInfoIterator{
public:
	DependencyTreeIterator(
		ModuleLoadOrderInfoIterator base,
		unsigned int * iterator_count_ptr
	) :
		ModuleLoadOrderInfoIterator(base),
		iterator_count_ptr(iterator_count_ptr)
	{
		*iterator_count_ptr += 1;
	}

	~DependencyTreeIterator(){
		if (iterator_count_ptr == nullptr) throw RLException(
			"Lowering iterator count of DependencyTree failed\n",
			"Pointer to iterator count not set\n",
			"DependencyTreeIterator::~DependencyTreeIterator()\n"
		);
		if (*iterator_count_ptr == 0) throw RLException(
			"Lowering iterator count of DependencyTree failed\n",
			"Iterator count is already zero\n",
			"DependencyTreeIterator::~DependencyTreeIterator()\n"
		);
		*iterator_count_ptr -= 1;
	}

	module_info_t * operator*(){
		return this->ModuleLoadOrderInfoIterator::operator*().module;
	}

private:
	unsigned int * iterator_count_ptr;
};


//- ---------------------- DependencyTree Implementation -----------------------


DependencyTree::DependencyTree(){
	// TODO: Implement
}

DependencyTree::~DependencyTree(){
	// TODO: Implement
}

void DependencyTree::addModule(module_info_t * mod){
	this->modules.push_back({
		.module = mod,
		.priority = 0,
		.visited = false,
	});
}

ModuleLoadOrderInfoIterator DependencyTree::cbegin() const noexcept{
	return DependencyTreeIterator(
		this->modules.cbegin(),
		&this->iterators
	);
}

ModuleLoadOrderInfoIterator DependencyTree::cend() const noexcept{
	return DependencyTreeIterator(
		this->modules.cend(),
		&this->iterators
	);
}


/*
def deps_satisfied(test, start, end):
	for dep in test.deps:
		for compared in range(start, end):
			if dep == compared:
				break
		else:
			return False
	return True

def find_loadable(start, next, end):
	for test in range(next, end):
		if deps_satisfied(test, start, next):
			return test
	raise MissingDeps(test)

for next_location in range(start, end):
	loadable = find_loadable(start, next_location, end)
	swap(loadable, next_location)
*/


bool areDependenciesSatisfied(module_dependency_t * deps, it start, it end){
	
}

void DependencyTree::sort(){
	// TODO: Implement
}

