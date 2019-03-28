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

/// Node - The base struct for any node which can be linked
/* abstract */ struct Node
{
public:
	/// Constructor
	Node();

	/// Destructor
	virtual ~Node();

	/// Check whether the node is valid or not. Pleaes note that a singleton node is not valid.
	bool isValid();

	/// Link after a node
	void linkAfter(Node& node);

	/// Link before a node
	void linkBefore(Node& node);

	/// Unlink
	void unlink();

	/// The previous node
	Node* prev;

	/// The next node
	Node* next;

};	// Node

/// Root for Dynamic (Heap Allocated) Nodes
struct RootForDynamicNodes : public Node
{
public:
	/// Destructor
	~RootForDynamicNodes();

};	// RootForDynamicNodes

/// Root for Static Nodes
struct RootForStaticNodes : public Node
{

};	// RootForStaticNodes

}	// microbit_dal_ext_kit

#endif	// EXT_KIT_NODE_H
