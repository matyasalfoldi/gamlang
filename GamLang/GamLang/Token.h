#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

enum class TokenType
{
    Identifier,
    IntegerLiteral,
    StringLiteral,

    KeywordInt,
    KeywordString,
    KeywordPrint,

    Plus,
    Minus,
    Star,

    Equals,

    LeftParen,
    RightParen,
    DoubleQuote,

    Semicolon,

    Empty,

    End
};

class Token
{
public:
    TokenType type;
    std::string text;
    int line;
    int column;
    Token()
        : type(TokenType::Empty), text(""), line(0), column(0)
    {}


    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

const std::map<TokenType, std::string> type_map{
    {TokenType::Identifier, "Identifier"},
    {TokenType::IntegerLiteral, "IntegerLiteral"},
    {TokenType::StringLiteral, "StringLiteral"},
    {TokenType::KeywordInt, "KeywordInt"},
    {TokenType::KeywordString, "KeywordString"},
    {TokenType::KeywordPrint, "KeywordPrint"},
    {TokenType::Plus, "Plus"},
    {TokenType::Minus, "Minus"},
    {TokenType::Star, "Star"},
    {TokenType::Equals, "Equals"},
    {TokenType::LeftParen, "LeftParen"},
    {TokenType::RightParen, "RightParen"},
    {TokenType::DoubleQuote, "DoubleQuote"},
    {TokenType::Semicolon, "Semicolon"},
    {TokenType::End, "$"}
};

inline std::ostream& operator<<(std::ostream& out, const Token& token)
{
    auto type_val = type_map.find(token.type);

    out << type_val->second << " " << token.text;
    return out;
}