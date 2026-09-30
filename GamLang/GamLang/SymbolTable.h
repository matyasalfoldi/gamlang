#pragma once

#include <string>
#include <unordered_map>

#include "AST.h"
#include "Token.h"

struct Symbol
{
	std::string name;
	std::string type;
};

struct SymbolTable
{
    std::unordered_map<std::string, Symbol> symbols;

    void add(const std::string& name, const std::string& type)
    {
        symbols.emplace(name, Symbol{ name, type });
    }
};

inline void build_symbol_table(const Program& program, SymbolTable& table)
{
    for (const auto& statement : program.statements)
    {
        if (auto* assignment =
            dynamic_cast<const AssignmentStatement*>(statement.get()))
        {
            table.add(assignment->id, assignment->type);
        }
    }
}
