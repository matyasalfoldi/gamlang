#include "LexerState.h"

void StartState::handle(LexerImp& lexer, char c)
{
    isspace(c);
    if ('\n' == c)
    {
        return;
    }
    if (c == '"')
    {
        lexer.add_token(TokenType::DoubleQuote, "\"");
        lexer.change_state(std::make_unique<StringState>());
        return;
    }

    if (c == ';')
    {
        lexer.add_token(TokenType::Semicolon, ";");
        return;
    }

    if (std::isdigit(static_cast<unsigned char>(c)))
    {
        lexer.append(c);
        lexer.change_state(std::make_unique<NumberState>());
        return;
    }

    if (std::isalpha(static_cast<unsigned char>(c)))
    {
        lexer.append(c);
        lexer.change_state(std::make_unique<IdentifierState>());
        return;
    }

    lexer.error(c);
}

void IdentifierState::handle(LexerImp& lexer, char c)
{
    if (std::isalpha(static_cast<unsigned char>(c)))
    {
        lexer.append(c);
        return;
    }

    if (std::isspace(static_cast<unsigned char>(c)))
    {
        TokenType t;
        if ("int" == lexer.current())
        {
            t = TokenType::KeywordInt;
        }
        else if ("string" == lexer.current())
        {
            t = TokenType::KeywordString;
        }
        else
        {
            lexer.error(c);
        }
        lexer.add_token(
            t,
            lexer.current());

        lexer.clear_current();
        lexer.change_state(std::make_unique<StartState>());
        return;
    }

    if (c == '=')
    {
        lexer.add_token(TokenType::Identifier,
            lexer.current());

        lexer.add_token(TokenType::Equals, "=");

        lexer.clear_current();
        lexer.change_state(std::make_unique<StartState>());
        return;
    }

    if (c == '+')
    {
        lexer.add_token(TokenType::Identifier,
            lexer.current());

        lexer.add_token(TokenType::Plus, "+");

        lexer.clear_current();
        lexer.change_state(std::make_unique<StartState>());
        return;
    }
    if (isspace(c))
    {
        return;
    }
    lexer.error(c);
}

void NumberState::handle(LexerImp& lexer, char c)
{
    if (std::isdigit(static_cast<unsigned char>(c)))
    {
        lexer.append(c);
        return;
    }

    if (c == '+')
    {
        lexer.add_token(
            TokenType::IntegerLiteral,
            lexer.current());

        lexer.add_token(TokenType::Plus, "+");

        lexer.clear_current();
        lexer.change_state(std::make_unique<StartState>());
        return;
    }

    if (c == ';')
    {
        lexer.add_token(
            TokenType::IntegerLiteral,
            lexer.current());

        lexer.add_token(TokenType::Semicolon, ";");

        lexer.clear_current();
        lexer.change_state(std::make_unique<StartState>());
        return;
    }

    lexer.error(c);
}

void StringState::handle(LexerImp& lexer, char c)
{
    if ('"' == c)
    {
        lexer.add_token(
            TokenType::StringLiteral,
            lexer.current());

        lexer.add_token(TokenType::DoubleQuote, "\"");

        lexer.clear_current();
        lexer.change_state(std::make_unique<StartState>());

        return;
    }

    lexer.append(c);
}
