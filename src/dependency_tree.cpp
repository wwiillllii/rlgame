#include "dependency_tree.h"
#include "rlexception.h"

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

using ModuleLoadOrderInfoIterator = DependencyTree::ModuleLoadOrderInfoIterator;

ModuleLoadOrderInfoIterator
	DependencyTree::cbegin() const noexcept
{
	// TODO: Implement
	ModuleLoadOrderInfoIterator it =  this->modules.cbegin();
	// it.
	return it;
}

ModuleLoadOrderInfoIterator
	DependencyTree::cend() const noexcept
{
	// TODO: Implement
	return this->modules.cend();
}


//			##################
//			# Iterator Stuff #
//			##################


class DependencyTreeIterator : public ModuleLoadOrderInfoIterator{
public:
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
	unsigned int * iterator_count_ptr;
};

