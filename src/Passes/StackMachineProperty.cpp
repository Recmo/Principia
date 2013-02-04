#include <Passes/StackMachineProperty.h>
#include <DFG/Node.h>
#include <DFG/Edge.h>

PropertyType StackMachineProperty::classType = PropertyType::StackVM;

StackMachineProperty::StackMachineProperty(const StackMachineProperty& copy)
: Property()
, _stack(copy._stack)
, _instructions()
{
	foreach(Instruction* instruction, copy._instructions)
		_instructions.push_back(instruction->clone());
}

StackMachineProperty::~StackMachineProperty()
{
	foreach(Instruction* instruction, _instructions)
		delete instruction;
}

void StackMachineProperty::print(std::wostream& out) const
{
	out << L"Stack: " << _stack << endl;
	foreach(Instruction* instruction, _instructions)
		instruction->print(out);
}

void StackMachineProperty::CallInstruction::print(std::wostream& out) const
{
	out << L"\t\tCall " << _node << L" " << _arguments << L" → " << _numReturns << endl;
}

void StackMachineProperty::AllocateInstruction::print(std::wostream& out) const
{
	out << L"\t\tAlloc " << _closure << endl;
}

void StackMachineProperty::StoreInstruction::print(std::wostream& out) const
{
	out << L"\t\tStore " << _closure << " " << _slot << " " << _value << endl;
}

void StackMachineProperty::ReturnInstruction::print(std::wostream& out) const
{
	out << L"\t\tReturn " << _returns << endl;
}