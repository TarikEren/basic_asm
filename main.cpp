#include "headers/Token.h"
#include "headers/Tokenizer.h"

/*
 * Supported tokens:
 *  INT A   : Stores an integer value named A
 *  ADD A B : Adds the values of integers A and B
 *  SUB A B : Subtracts the value B from B
 *  MUL A B : Multiplies the values of integers A and B
 *  DIV A B : Divides the value A by B
 *  SAV C   : Saves the data stored by the buffer to the storage with the name C
 *  INC A   : Increments the value of A by one
 *
 * */

int main() {
    auto* tokenizer_obj = new Tokenizer;
    tokenizer_obj->read_file("test.txt");
//    tokenizer_obj->read_file(argv[1]); //Uncomment at the end.
//    Paste int argc, char** argv into the main function parameter list.
    tokenizer_obj->tokenize();
    if (tokenizer_obj->token_check()) {
        tokenizer_obj->execute();
    }
    tokenizer_obj->print_tokens();
    tokenizer_obj->print_storage();
    tokenizer_obj->clear_storage();
    tokenizer_obj->clear_tokens();
    delete tokenizer_obj;
    return 0;
}