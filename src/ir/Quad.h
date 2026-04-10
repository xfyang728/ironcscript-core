#pragma once
#include<list>
#include<string>
#include<iostream>

namespace cse {

enum OpEnum
{
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	EQ,
	NE,
	LT,
	LE,
	GT,
	GE,
	ASSIGN,
	JMP,
	JMPF,
	JMPT,
	CALL,
	PARAM,
	RET,
	RETURN,
	LABEL,
	FUNC,
	ENDFUNC,
	XOR,
	AND,
	OR,
	NOT,
	LSHIFT,
	RSHIFT,
	LOGICAL_AND,
	LOGICAL_OR,
	LOGICAL_NOT,
	SWITCH,
	CASE,
	DEFAULT,
	ARRAY,
	ARRAY_LOAD,
	ARRAY_STORE,
	ADDRESS_OF,
	DEREFERENCE,
	STORE_DEREFERENCE,
	CAST,
	SET_AL,
	STRING_CONCAT,
	MEMBER_ACCESS,
	MEMBER_STORE,
	EXTERN,
	REGISTER_CALLBACK,
	THROW,
	POP
};

inline std::string opToString(OpEnum op)
{
	switch (op) {
	case ADD: return "ADD";
	case SUB: return "SUB";
	case MUL: return "MUL";
	case DIV: return "DIV";
	case MOD: return "MOD";
	case EQ: return "EQ";
	case NE: return "NE";
	case LT: return "LT";
	case LE: return "LE";
	case GT: return "GT";
	case GE: return "GE";
	case ASSIGN: return "ASSIGN";
	case JMP: return "JMP";
	case JMPF: return "JMPF";
	case JMPT: return "JMPT";
	case CALL: return "CALL";
	case PARAM: return "PARAM";
	case RET: return "RET";
	case RETURN: return "RETURN";
	case LABEL: return "LABEL";
	case FUNC: return "FUNC";
	case ENDFUNC: return "ENDFUNC";
	case XOR: return "XOR";
	case AND: return "AND";
	case OR: return "OR";
	case NOT: return "NOT";
	case LSHIFT: return "LSHIFT";
	case RSHIFT: return "RSHIFT";
	case LOGICAL_AND: return "LOGICAL_AND";
	case LOGICAL_OR: return "LOGICAL_OR";
	case LOGICAL_NOT: return "LOGICAL_NOT";
	case SWITCH: return "SWITCH";
	case CASE: return "CASE";
	case DEFAULT: return "DEFAULT";
	case ARRAY: return "ARRAY";
	case ARRAY_LOAD: return "ARRAY_LOAD";
	case ARRAY_STORE: return "ARRAY_STORE";
	case ADDRESS_OF: return "ADDRESS_OF";
	case DEREFERENCE: return "DEREFERENCE";
	case STORE_DEREFERENCE: return "STORE_DEREFERENCE";
	case CAST: return "CAST";
	case SET_AL: return "SET_AL";
	case STRING_CONCAT: return "STRING_CONCAT";
	case MEMBER_ACCESS: return "MEMBER_ACCESS";
	case MEMBER_STORE: return "MEMBER_STORE";
	case EXTERN: return "EXTERN";
	case REGISTER_CALLBACK: return "REGISTER_CALLBACK";
	case THROW: return "THROW";
	case POP: return "POP";
	default: return "UNKNOWN";
	}
}

inline OpEnum stringToOp(const std::string& op) {
	if (op == "=" || op == "ASSIGN") return OpEnum::ASSIGN;
	if (op == "+") return OpEnum::ADD;
	if (op == "-") return OpEnum::SUB;
	if (op == "*") return OpEnum::MUL;
	if (op == "/") return OpEnum::DIV;
	if (op == "%") return OpEnum::MOD;
	if (op == "==") return OpEnum::EQ;
	if (op == "!=") return OpEnum::NE;
	if (op == "<") return OpEnum::LT;
	if (op == "<=") return OpEnum::LE;
	if (op == ">") return OpEnum::GT;
	if (op == ">=") return OpEnum::GE;
	if (op == "&&") return OpEnum::AND;
	if (op == "||") return OpEnum::OR;
	if (op == "!") return OpEnum::NOT;
	if (op == "^") return OpEnum::XOR;
	if (op == "&") return OpEnum::AND;
	if (op == "|") return OpEnum::OR;
	if (op == "<<") return OpEnum::LSHIFT;
	if (op == ">>") return OpEnum::RSHIFT;
	if (op == "neg") return OpEnum::SUB;
	if (op == "~") return OpEnum::NOT;
	if (op == "goto") return OpEnum::JMP;
	if (op == "ifFalse") return OpEnum::JMPF;
	if (op == "ifTrue") return OpEnum::JMPT;
	if (op == "label") return OpEnum::LABEL;
	if (op == "func") return OpEnum::FUNC;
	if (op == "endfunc") return OpEnum::ENDFUNC;
	if (op == "return") return OpEnum::RETURN;
	if (op == "call") return OpEnum::CALL;
	if (op == "param") return OpEnum::PARAM;
	if (op == "?:") return OpEnum::NE;
	if (op == "[]=") return OpEnum::ASSIGN;
	if (op == ".") return OpEnum::ASSIGN;
	if (op == "*=") return OpEnum::ASSIGN;
	if (op == "++") return OpEnum::ADD;
	if (op == "--") return OpEnum::SUB;
	return OpEnum::ASSIGN;
}

class Quad
{
	OpEnum op;
	std::string arg1;
	std::string arg2;
	std::string result;
public:
	Quad() {};
	~Quad();
	Quad(OpEnum op, const std::string& arg1, const std::string& arg2, const std::string& result);
	
	// Getter methods
	OpEnum getOp() const { return op; }
	const std::string& getArg1() const { return arg1; }
	const std::string& getArg2() const { return arg2; }
	const std::string& getResult() const { return result; }

	// Setter methods
	void setResult(const std::string& r) { result = r; }
	void setArg1(const std::string& a) { arg1 = a; }
	void setArg2(const std::string& a) { arg2 = a; }
	void setOp(OpEnum o) { op = o; }
	
	void print() const {
		std::cout << opToString(op) << " " 
		          << arg1 << " " 
		          << arg2 << " " 
		          << result << std::endl;
	}
};

} // namespace cse

