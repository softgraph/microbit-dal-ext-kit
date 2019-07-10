/// The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)
/**	@package	microbit_dal_ext_kit
*/

/// Gesture utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "ExtKitNode.h"	// self
#include "ExtKit.h"

namespace microbit_dal_ext_kit {

/**	@struct Node
*/

Node::Node()
{
	next = this;
	prev = this;
}

Node::~Node()
{
}

bool Node::isValid()
{
	return next && prev && (next != this) && (prev != this);
}

void Node::linkAfter(Node& node)
{
	prev = &node;
	next = node.next;
	next->prev = this;
	prev->next = this;
}

void Node::linkBefore(Node& node)
{
	next = &node;
	prev = node.prev;
	next->prev = this;
	prev->next = this;
}

void Node::unlink()
{
	prev->next = next;
	next->prev = prev;
	next = this;
	prev = this;
}

/**	@struct RootForDynamicNodes
*/

RootForDynamicNodes::~RootForDynamicNodes()
{
	Node* p = this;
	while((p = p->next) != this) {
		EXT_KIT_ASSERT_OR_PANIC(p && p->isValid(), panic::kCorruptedNode);

		Node* r = p;
		p = r->prev;	// rewind p
		r->unlink();	// unlink and delete r
		delete r;
	}
}

}	// microbit_dal_ext_kit
