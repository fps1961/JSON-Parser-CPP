#include <fstream>
#include <iostream>

#include "JsonException.h"
#include "Lexer.h"
#include "Parser.h"

std::string getFileData(const std::string& file_path)
{
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open())
    {
        std::cerr << "File invalid. Is the path or file name correct?\n";
        exit(1);
    }


    const std::istreambuf_iterator<char> it{file_stream}, end;
    std::string data{it, end};
    return data;
}


int main(const int argc, char** argv)
{
    if (argc == 1)
    {
        throw std::runtime_error("No File Provided");
    }

    try
    {
        const auto input = getFileData(argv[1]);

        auto lexer = Lexer(input);

        const auto& token_list = lexer.tokenize();

        auto parser = Parser(token_list);
        parser.parse();


        std::cout << "Valid File!\n";
        return 0;
    }
    catch (const JsonException& e)
    {
        std::cerr << e.what();
        exit(1);
    }
}
