#pragma once

#include <string>

//Might merge the ADD, SUM, MUL and DIV tokens into one token later on for simplicity's sake.
//It's not really necessary though.

typedef struct Token {
    std::string type{};
    virtual ~Token() = default;
}Token;

typedef struct StartToken: Token {} StartToken;

typedef struct EndToken: Token {} EndToken;

typedef struct IntToken: Token {
    int value;
    std::string name;
    bool heapAllocated = false;
}IntToken;

typedef struct AddToken: Token {
    std::string l_name{};
    std::string r_name{};
    int result;
}AddToken;

typedef struct SubToken: Token {
    std::string l_name{};
    std::string r_name{};
    int result;
}SubToken;

typedef struct MulToken: Token {
    std::string l_name{};
    std::string r_name{};
    int result;
}MulToken;

typedef struct DivToken: Token {
    std::string l_name{};
    std::string r_name{};
    int result;
}DivToken;

typedef struct SaveToken: Token {
    std::string target_name{};
}SaveToken;

typedef struct PrintToken: Token {
    std::string target_name{};
}PrintToken;

typedef struct IncToken: Token {
    std::string target_name{};
}IncToken;