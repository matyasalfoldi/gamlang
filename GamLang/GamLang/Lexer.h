#pragma once

#include <ctype.h>
#include <map>
#include <set>
#include <vector>

#include "Token.h"

enum class LexerState
{
    Start,
    Identifier,
    Number,
    String,
    Error
};

const std::map<LexerState, std::string> lexer_map{
    {LexerState::Identifier, "Identifier"},
    {LexerState::Number, "Number"},
    {LexerState::Start, "Start"},
    {LexerState::String, "String"},
    {LexerState::Error, "Error"}
};

inline std::ostream& operator<<(std::ostream& out, const LexerState& state)
{

    auto type_val = lexer_map.find(state);
    out << type_val->second << std::endl;
    return out;
}

class Lexer
{
public:
    // INNER TYPES

    void create_tokens(std::string content);
    void print_tokens()
    {
        for (auto t : tokens)
        {
            std::cout << t << std::endl;
        }
    }

private:
    // VARIABLES
    std::set<std::string> identifiers;
    std::vector<Token> tokens;
    Token token;
    LexerState state = LexerState::Start;
    std::string current_part = "";

    // HELPERS
    bool is_keyword()
    {
        std::string tmp = current_part;
        if (std::string("string").starts_with(tmp))
        {
            return true;
        }
        else if (std::string("int").starts_with(tmp))
        {
            return true;
        }
        return false;
    }
    bool is_identifier()
    {
        auto it = identifiers.lower_bound(current_part);
        return it != identifiers.end() &&
            it->compare(0, current_part.size(), current_part) == 0;
    }

    // MODIFIERS
    void set_token(TokenType token_type, std::string text)
    {
        token.type = token_type;
        token.text = text;
        if (TokenType::Identifier == token_type)
        {
            identifiers.insert(text);
        }
    }
    void set_state(LexerState new_state)
    {
        //std::cout << "Setting state to:" << new_state << std::endl;
        state = new_state;
    }
    void commit_token()
    {
        tokens.push_back(token);
    }
    void clean_tmp_values()
    {
        token.type = TokenType::Empty;
        token.text = "";
        current_part = "";
    }

    // STATES
    void start_state(const char c);
    void identifier_state(const char c);
    void number_state(const char c);
    void string_state(const char c);
    void error_state(const char c);

};
