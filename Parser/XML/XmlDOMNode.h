/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef XmlDOM_NODE_H_
#define XmlDOM_NODE_H_

#include <string>

#include  "XmlDOMData.h"
#include  "XmlDOMAttribute.h"

//namespace XmlDOM {


class Node {
public:
	typedef std::string TEXT;

	private:
		Data data;
		TEXT nodeName;
		Attribute attributes;

		Node *parentNode;
		Node *previousSibling;
		Node *nextSibling;
		Node *firstChild;
		Node *lastChild;

		Node *self;

	public:
		// constructors
		Node();
		//Node(Data value);
		// getter const
		TEXT getNodeName() const;
		Node * getParentNode() const;
		Node * getNextSibling() const;
		Node * getFirstChild() const;
		Node * getPreviousSibling() const;
		Node * getLastChild() const;
		Node * getSelfRef() const;
		Data getData() const;
		TEXT getAttribute(TEXT key) const;
		Attribute getAttributes() const;

		// setter
		void setNodeName(TEXT name);
		void setParentNode(Node *parent);
		void setNextSibling(Node *sibling);
		void setPreviousSibling(Node *sibling);
		void setData(Data nodeData);
		void setAttribute(TEXT key, TEXT value);
		void setAttributes(Attribute attributes);

		void addChild(Node *child);
};

#endif // XmlDOM_NODE_H_
