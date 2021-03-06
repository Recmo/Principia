#pragma once
#include <DFG/Node.h>
#include <DFG/Value.h>
#include <Parser/SourceProperty.h>

class ParseTree
{
public:
	ParseTree();
	~ParseTree();
	
	class Node;
	class Statement;
	class Scope;
	class Identifier;
	class Constant;
	class IdentifierVisible;
	class IdentifierLookup;
	
	const Scope* top() const { return _top; }
	Scope* top() { return _top; }
	
	void print(std::wostream& out) const;
	bool validate() const;
	
	void uniqueifyNames();
	
private:
	Scope* _top;
};

inline std::wostream& operator<<(std::wostream& out, const ParseTree& tree)
{
	tree.print(out);
	return out;
}

class ParseTree::Node
{
public:
	virtual ~Node();
	
	virtual void print(std::wostream& out, uint indentation = 0) const = 0;
	virtual bool validate() const;
	
	SourceProperty source() const { return _source; }
	void source(const SourceProperty& source) { _source = source; }
	
	Node* parent() const { return _parent; }
	uint indexInParent() const { return _indexInParent; }
	Node* prevSibbling() const;
	Node* nextSibbling() const;
	Node* firstChild() const;
	Node* lastChild() const;
	uint numChildren() const { return _children.size(); }
	Node* child(uint index) const;
	const std::vector<Node*>& children() const { return _children; }
	
	void replaceWith(Node* node);
	void appendChild(Node* child);
	void insertChild(Node* child, uint position);
	void insertBefore(Node* child, Node* newChild);
	void insertAfter(Node* child, Node* newChild);
	void removeChild(Node* child);
	void removeChild(uint position);
	void swapChild(Node* currentChild, Node* newChild);
	void swapChild(uint position, Node* newChild);
	
	Scope* enclosingScope() const;
	
	template<class T>
	bool isA() const { return dynamic_cast<const T*>(this) != nullptr; }
	
	template<class T>
	T* to() { return dynamic_cast<T*>(this); }
	
	template<class T>
	const T* to() const { return dynamic_cast<T*>(this); }
	
protected:
	Node();
	Node* _parent;
	uint _indexInParent;
	std::vector<Node*> _children;
	SourceProperty _source;
};

class ParseTree::Scope: public Node
{
public:
	Scope() { }
	virtual ~Scope() { }
	virtual void print(std::wostream& out, uint indentation = 0) const;
	
	Statement* associatedStatement() const;
};

class ParseTree::Identifier: public Node
{
public:
	Identifier(): _name(), _outbound(false), _bindingSite(nullptr) { }
	virtual ~Identifier() { }
	
	const std::wstring& name() const { return _name; }
	Identifier& name(const std::wstring& value) { _name = value; return *this; }
	
	bool outbound() const { return _outbound; }
	bool inbound() const { return !_outbound; }
	Identifier& setOutbound() { _outbound = true; return *this; }
	Identifier& setInbound() { _outbound = false; return *this; }
	
	Identifier* bindingSite() const { return _bindingSite; }
	Identifier& bindingSite(Identifier* value) { _bindingSite = value; return *this; }
	
	virtual void print(std::wostream& out, uint indentation = 0) const;
	
private:
	std::wstring _name;
	bool _outbound;
	Identifier* _bindingSite;
};

class ParseTree::Constant: public Node
{
public:
	Constant(Value value): _value(value) { }
	virtual ~Constant() { }
	
	Value value() const { return _value; }
	Constant& value(Value val) { _value = val; return *this; }
	
	virtual void print(std::wostream& out, uint indentation = 0) const;
	
private:
	Value _value;
};

class ParseTree::Statement: public Node
{
public:
	enum Type {
		Call,
		Closure,
		Precondition,
		Postcondition,
		Axiom,
		Assertion
	};
	
	Statement(Type type = Call): _type(type) { }
	virtual ~Statement() { }
	
	Type type() const { return _type; }
	Statement& type(Type value) { _type = value; return *this; }
	
	std::vector<Identifier*> out() const;
	std::vector<Node*> in() const;
	
	Statement& addOut(Identifier* value);
	Statement& addIn(Node* value);
	
	bool isInline() const;
	
	Scope* associatedScope(bool create = false);
	
	virtual void print(std::wostream& out, uint indentation = 0) const;
	
private:
	Type _type;
};

class ParseTree::IdentifierVisible: public Node
{
public:
	IdentifierVisible(Identifier* identifier): _identifier(identifier) { }
	virtual ~IdentifierVisible() { }
	
	Identifier* identifier() const { return _identifier; }
	
	virtual void print(std::wostream& out, uint indentation = 0) const;
	
private:
	Identifier* _identifier;
};

class ParseTree::IdentifierLookup: public Node
{
public:
	IdentifierLookup(Identifier* identifier): _identifier(identifier) { }
	virtual ~IdentifierLookup() { }
	
	Identifier* identifier() const { return _identifier; }
	
	virtual void print(std::wostream& out, uint indentation = 0) const;
	
private:
	Identifier* _identifier;
};

inline std::wostream& operator<<(std::wostream& out, const ParseTree::Node& node)
{
	node.print(out);
	return out;
}

inline std::wostream& operator<<(std::wostream& out, const ParseTree::Node* node)
{
	if(node)
		node->print(out);
	else
		out << L"<null>";
	return out;
}
