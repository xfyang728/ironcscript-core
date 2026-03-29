#include "Quad.h"

namespace cse {

Quad::Quad(OpEnum op, const std::string& arg1, const std::string& arg2, const std::string& result)
{
	this->op = op;
	this->arg1 = arg1;
	this->arg2 = arg2;
	this->result = result;
}

Quad::~Quad()
{
}

} // namespace cse

