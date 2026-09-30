#pragma once

#include <memory>
#include <string>
#include <vector>

struct Expr
{
	virtual ~Expr() = default;
	virtual std::string dump() = 0;
};

struct IntExpr : Expr
{
	int val;
	IntExpr(int _val) : val(_val) {}

	std::string dump()
	{
		return std::to_string(val);
	}
};

struct StringExpr : Expr
{
	std::string val;

	StringExpr(std::string _val)
	: val(std::move(_val)) { }

	std::string dump()
	{
		return val;
	}
};

struct IdentifierExpr : Expr
{
	std::string name;
	IdentifierExpr(std::string _name)
	: name(std::move(_name)) { }

	std::string dump()
	{
		return name;
	}
};

struct BinaryExpr : Expr
{
	std::string op;
	std::unique_ptr<Expr> left;
	std::unique_ptr<Expr> right;

	BinaryExpr(auto _op, auto _left, auto _right)
	: op(_op), left(std::move(_left)), right(std::move(_right)) {}

	std::string dump()
	{
		return left->dump() + " " + right->dump();
	}
};

struct Statement
{
	virtual ~Statement() = default;
	virtual std::string dump() = 0;
};

struct AssignmentStatement : Statement
{
	std::string type;
	std::string id;
	std::unique_ptr<Expr> val;

	AssignmentStatement(std::string _type, std::string _id, auto _val)
		:type(_type), id(_id), val(std::move(_val)) {}

	std::string dump()
	{
		return "Type: " + type + " Id: " + id + " val: " + val->dump();
	}
};

struct Program
{
	std::vector<std::unique_ptr<Statement>> statements;

};
