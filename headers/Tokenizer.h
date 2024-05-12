#pragma once

#include <string>
#include <vector>
#include "Token.h"

typedef struct Tokenizer {
    std::string input;
    char cur{};
    size_t i{};
    std::string buffer;
    std::vector<Token*> tokens;
    void read_file(const std::string& file_name);
    void consume();
    void tokenize();
    void print_tokens();
    bool token_check();
    void clear_tokens();
    void execute();
    char peek();
    std::vector<IntToken*> storage;
    void print_storage();
    void clear_storage();
}Tokenizer;

