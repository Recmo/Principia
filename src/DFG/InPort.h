#pragma once
#include <DFG/Port.h>
#include <memory>
#include <iostream>
class Node;
class OutPort;
class Value;

class InPort: public Port, public std::enable_shared_from_this<InPort>
{
public:
	InPort(Node& parent, uint index): Port(parent, index) { }
	
	std::shared_ptr<OutPort> source() const { return _source.lock(); }
	
	void clear();
	InPort& operator<<(OutPort& port);
	InPort& operator<<(const Value& value);
	
private:
	std::weak_ptr<OutPort> _source;
};

std::wostream& operator<<(std::wostream& out, const InPort& value);
