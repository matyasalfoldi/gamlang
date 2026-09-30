#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Token.h"

class LexerImp;

class LexerState
{
protected:
    bool isspace(char c)
    {
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            return true;
        }
        return false;
    }

public:
	virtual ~LexerState() = default;
	virtual void handle(LexerImp& lexer, char c) = 0;
};

class StartState : public LexerState
{
public:
    void handle(LexerImp& lexer, char c) override;
};

class IdentifierState : public LexerState
{
public:
    void handle(LexerImp& lexer, char c) override;
};

class NumberState : public LexerState
{
public:
    void handle(LexerImp& lexer, char c) override;
};

class StringState : public LexerState
{
public:
    void handle(LexerImp& lexer, char c) override;
};

class LexerImp
{
public:
    LexerImp()
    {
        state = std::make_unique<StartState>();
    }

    void create_tokens(const std::string& content)
    {
        for (char c : content)
        {
            state->handle(*this, c);
        }
    }

    void change_state(std::unique_ptr<LexerState> _state)
    {
        state = std::move(_state);
    }

    void add_token(TokenType type, const std::string& text)
    {
        Token token;
        token.type = type;
        token.text = text;
        tokens.push_back(token);
    }

    void append(char c)
    {
        current_part += c;
    }

    const std::string& current() const
    {
        return current_part;
    }

    void clear_current()
    {
        current_part = "";
    }

    void print_tokens() const
    {
        for (auto t : tokens)
        {
            std::cout << t << std::endl;
        }
    }

    void error(const char c)
    {
        std::cout << "Incorrect value: " << c << " after: " << current_part << std::endl;
        std::exit(1);
    }
private:
    std::vector<Token> tokens;
    std::string current_part;

    std::unique_ptr<LexerState> state;
};
