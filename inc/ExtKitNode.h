/// Yotta module microbit-dal-ext-kit
/**	@package	microbit_dal_ext_kit
*/

/// Node utility
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef EXT_KIT_NODE_H
#define EXT_KIT_NODE_H

#include "ExtKit_Common.h"

namespace microbit_dal_ext_kit {

/// Node. The base struct for any node which can be linked.
/* virtual */ struct Node
{
	/// The previous node.
	Node* prev;

	/// The next node.
	Node* next;

	/// Constructor.
	Node();

	/// Destructor.
	virtual /* to be overridden */ ~Node();

	/// Link after a node.
	void linkAfter(Node& node);

	/// Link before a node.
	void linkBefore(Node& node);

	/// Unlink.
	void unlink();
};

inline Node::Node()
{
	next = this;
	prev = this;
}

inline /* to be overridden */ Node::~Node()
{
}

inline void Node::linkAfter(Node& node)
{
	prev = &node;
	next = node.next;
	next->prev = this;
	prev->next = this;
}

inline void Node::linkBefore(Node& node)
{
	next = &node;
	prev = node.prev;
	next->prev = this;
	prev->next = this;
}

inline void Node::unlink()
{
	prev->next = next;
	next->prev = prev;
	next = this;
	prev = this;
}

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_NODE_H
