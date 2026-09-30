// GamLang.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

//#include "Lexer.h"
#include "LexerState.h"

int main()
{
    std::string file_path;
    std::cout << "Write the full path to the file to compile" << std::endl;
    std::getline(std::cin, file_path);
    std::cout << "Input file: " << file_path << std::endl;
    if (std::filesystem::exists(file_path))
    {
        std::ifstream to_compile(file_path);
        std::stringstream buffer;
        buffer << to_compile.rdbuf();
        std::string file_contents = buffer.str();
        to_compile.close();
        LexerImp lexer;
        lexer.create_tokens(file_contents);
        lexer.print_tokens();
    }
    else
    {
        std::cout << "File does not exist!" << std::endl;
    }
}
