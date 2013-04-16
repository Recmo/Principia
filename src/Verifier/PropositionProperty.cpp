#include "Verifier/PropositionProperty.h"
#include <DFG/Node.h>

PropertyType PropositionProperty::classType = PropertyType::Proposition;

PropositionProperty::PropositionProperty()
: _preconditions()
, _axioms()
, _assertions()
, _postconditions()
{
}

PropositionProperty::PropositionProperty(const PropositionProperty& copy)
: _preconditions(copy._preconditions)
, _axioms(copy._axioms)
, _assertions(copy._assertions)
, _postconditions(copy._postconditions)
{
}

PropositionProperty::~PropositionProperty()
{
}

PropositionProperty& PropositionProperty::operator=(const PropositionProperty& copy)
{
	_preconditions = copy._preconditions;
	_axioms = copy._axioms;
	_assertions = copy._assertions;
	_postconditions = copy._postconditions;
}

void PropositionProperty::print(std::wostream& out) const
{
	out << _preconditions, _axioms, _assertions, _postconditions;
}
