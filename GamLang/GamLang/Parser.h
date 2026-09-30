#pragma once

#include <memory>
#include <vector>

#include "AST.h"
#include "Token.h"

// Recursive descent parser

class Parser
{
public:
	Parser(auto _tokens) : tokens(_tokens) {}
	Program parse()
	{
		return parse_program();
	}
private:
	std::vector<Token> tokens;
	std::uint32_t pos = 0;

	Token peek() const
	{
		return tokens[pos];
	}

	Token consume()
	{
		return tokens[pos++];
	}

	bool check(TokenType type) const
	{
		return peek().type == type;
	}

	Token expect(TokenType type)
	{
		if (!check(type))
		{
			//std::cout << type_map.find(type)->second << std::endl;
			throw std::runtime_error("Unexpected token");
		}

		return consume();
	}

	Program parse_program()
	{
		Program program;
		while (peek().type != TokenType::End)
		{
			program.statements.push_back(std::move(parse_statement()));
		}
		return program;
	}

	std::unique_ptr<Statement> parse_statement()
	{
		return parse_assignment();
	}

	std::unique_ptr<AssignmentStatement> parse_assignment()
	{
		std::string type = parse_type();
		std::string name = expect(TokenType::Identifier).text;
		expect(TokenType::Equals);
		auto expr = parse_expr();
		expect(TokenType::Semicolon);

		auto assignment = std::make_unique<AssignmentStatement>(type, name, std::move(expr));

		return assignment;
	}

	std::string parse_type()
	{
		if (check(TokenType::KeywordInt) || check(TokenType::KeywordString))
		{
			auto kw = consume();
			return type_map.find(kw.type)->second;
		}

		throw std::runtime_error("Assignment has to start with int or string");
	}

	std::unique_ptr<Expr> parse_expr()
	{
		if (peek().type == TokenType::IntegerLiteral || peek().type == TokenType::Identifier)
		{
			return parse_int_expr();
		}
	}

	std::unique_ptr<Expr> parse_int_expr()
	{
		auto left = parse_final();

		while(
			check(TokenType::Plus) ||
			check(TokenType::Minus) ||
			check(TokenType::Star))
		{
			auto op = consume().text;

			auto right = parse_final();

			auto binary = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));

			left = std::move(binary);
		}

		return left;
	}

	std::unique_ptr<Expr> parse_final()
	{
		if (check(TokenType::IntegerLiteral))
		{
			auto lit = consume();
			auto int_literal = std::make_unique<IntExpr>(stoi(lit.text));
			return int_literal;
		}
		else if (check(TokenType::Identifier))
		{
			auto id = consume();
			auto id_expr = std::make_unique<IdentifierExpr>(id.text);
			return id_expr;
		}
		throw std::runtime_error("final needs to be integer literal or identifier");
	}
};

