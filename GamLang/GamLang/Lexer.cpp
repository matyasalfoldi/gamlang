#include "Lexer.h"
// Deprecated first version
#include <iostream>

void Lexer::create_tokens(std::string content)
{
	
	for (auto c = content.cbegin(); c != content.cend(); ++c)
	{
		switch (state)
		{
		case LexerState::Start:
			start_state(*c);
			break;
		case LexerState::Identifier:
			identifier_state(*c);
			break;
		case LexerState::Number:
			number_state(*c);
			break;
		case LexerState::String:
			string_state(*c);
			break;
		case LexerState::Error:
			error_state(*c);
			break;
		default:
			break;
		}
		
	}
}

void Lexer::start_state(const char c)
{
	//std::cout << "curr: " << current_part << "start: " << c << std::endl;
	if ('\n' == c)
	{
		return;
	}
	else if ('"' == c)
	{
		set_token(TokenType::DoubleQuote, "\"");
		commit_token();

		set_state(LexerState::String);

		clean_tmp_values();
		return;
	}
	else if (';' == c)
	{
		set_token(TokenType::Semicolon, ";");
		commit_token();

		set_state(LexerState::Start);

		clean_tmp_values();
		return;
	}
	current_part += c;
	//std::cout << "Current: " << current_part << std::endl;

	if (isdigit(c))
	{
		set_state(LexerState::Number);
	}
	else if (is_keyword())
	{
		set_state(LexerState::Identifier);
	}
	else if (is_identifier())
	{
		set_state(LexerState::Identifier);
	}
	else
	{
		error_state(c);
	}
}

void Lexer::identifier_state(const char c)
{
	//std::cout << "curr: " << current_part << " id: " << c << std::endl;
	if (' ' == c)
	{
		return;
	}

	if ('=' == c)
	{
		set_token(TokenType::Identifier, current_part);
		commit_token();

		set_token(TokenType::Equals, "=");
		commit_token();

		set_state(LexerState::Start);

		clean_tmp_values();
	}
	else if ('+' == c)
	{
		set_token(TokenType::Identifier, current_part);
		commit_token();

		set_token(TokenType::Plus, "+");
		commit_token();

		set_state(LexerState::Start);

		clean_tmp_values();
	}
	else
	{
		if (isalpha(c))
		{
			current_part += c;
		}
		else
		{
			error_state(c);
		}

		if (current_part == "int")
		{
			set_token(TokenType::KeywordInt, current_part);
			commit_token();

			set_state(LexerState::Identifier);

			clean_tmp_values();
		}
		else if (current_part == "string")
		{
			set_token(TokenType::KeywordString, current_part);
			commit_token();

			set_state(LexerState::Identifier);

			clean_tmp_values();
		}
	}
}

void Lexer::number_state(const char c)
{
	//std::cout << "curr: " << current_part << " num: " << c << std::endl;
	if (';' == c)
	{
		set_token(TokenType::IntegerLiteral, current_part);
		commit_token();

		set_token(TokenType::Semicolon, ";");
		commit_token();

		set_state(LexerState::Start);

		clean_tmp_values();
	}
	else if ('+' == c)
	{
		set_token(TokenType::IntegerLiteral, current_part);
		commit_token();

		set_token(TokenType::Plus, "+");
		commit_token();

		set_state(LexerState::Start);

		clean_tmp_values();
	}
	else
	{
		if (isdigit(c))
		{
			set_state(LexerState::Number);
		}
		else if (isalpha(c))
		{
			error_state(c);
		}

		current_part += c;
	}
}

void Lexer::string_state(const char c)
{
	//std::cout << "curr: " << current_part << " str: " << c << std::endl;
	if ('"' == c)
	{
		set_token(TokenType::StringLiteral, current_part);
		commit_token();

		set_token(TokenType::DoubleQuote, "\"");
		commit_token();

		set_state(LexerState::Start);

		clean_tmp_values();
	}
	else
	{
		current_part += c;
	}
}

void Lexer::error_state(const char c)
{
	std::cout << "Incorrect value: " << c << " after: " << current_part << std::endl;
	std::exit(1);
}
