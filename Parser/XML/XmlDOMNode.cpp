/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#include "XmlDOMNode.h"

//using namespace XmlDOM;
Node::Node():
	data(""),
	parentNode(NULL),
	previousSibling(NULL),
	nextSibling(NULL),
	firstChild(NULL),
	lastChild(NULL),
	self(this)
{
}
/*
Node::Node(Data value):
	data(value),
	parentNode(NULL),
	lastChild(NULL),
	firstChild(NULL),
	previousSibling(NULL),
	nextSibling(NULL),
	self(this)
{
}*/

// getter const functions
Node::TEXT Node::getNodeName() const
{
	return nodeName;
}

Node * Node::getParentNode() const
{
	return parentNode;
}

Node * Node::getPreviousSibling() const
{
	return previousSibling;
}

Node * Node::getNextSibling() const
{
	return nextSibling;
}

Node * Node::getFirstChild() const
{
	return firstChild;
}

Node * Node::getLastChild() const
{
	return lastChild;
}

Node * Node::getSelfRef() const
{
	return self;
}

Data Node::getData() const
{
	return data;
}

Attribute Node::getAttributes() const
{
	return attributes;
}

Node::TEXT Node::getAttribute(TEXT key) const
{
	return attributes.getValue(key);
}


// setter functions
void Node::setNodeName(TEXT name)
{
	nodeName = name;
}

void Node::setParentNode(Node *parent)
{
	parentNode = parent;
}

void Node::setNextSibling(Node *sibling)
{
	nextSibling = sibling;
}

void Node::setPreviousSibling(Node *sibling)
{
	previousSibling = sibling;
}

void Node::setData(Data nodeData)
{
	data = nodeData;
}

void Node::setAttribute(TEXT key, TEXT value)
{
	attributes.setValue(key, value);
}

void Node::setAttributes(Attribute attr)
{
	attributes = attr;
}


// Function over basic utilities
void Node::addChild(Node *child)
{
	if (child == NULL) {
		return ;
	}

	if (firstChild == NULL) {
		firstChild = child;
	} else {
		lastChild->setNextSibling(child);
		child->setPreviousSibling(lastChild);
	}

	child->setParentNode(this);//getSelfRef());
	lastChild = child;
}
