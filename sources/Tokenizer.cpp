#include <sstream>
#include <fstream>
#include <iostream>
#include "../headers/Tokenizer.h"

void Tokenizer::consume() {
    this->i += 1;
    this->cur = this->input[this->i];
}

void Tokenizer::tokenize() {
    this->i = 0;
    this->cur = this->input[this->i];
    while (this->cur != '\0' && this->i != this->input.size()) {
        while (isalpha(this->cur)) {
            this->buffer.push_back(this->cur);
            consume();
            if (this->buffer == "STR") {
                auto* start = new StartToken;
                start->type = "STR";
                this->tokens.push_back(start);
                this->buffer.clear();
            }
            else if (this->buffer == "END") {
                auto* end = new EndToken;
                end->type = "END";
                this->tokens.push_back(end);
                this->buffer.clear();
            }
            else if (this->buffer == "INT") {
                auto* Int = new IntToken;
                Int->value = 0;
                Int->type = "INT";
                this->tokens.push_back(Int);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    Int->name.push_back(this->cur);
                    consume();
                }
                consume();
                while (isdigit(this->cur)) {
                    Int->value *= 10;
                    Int->value += this->cur - 0x30;
                    consume();
                }
            }
            else if (this->buffer == "ADD") {
                auto* add = new AddToken;
                add->type = "ADD";
                this->tokens.push_back(add);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    add->l_name.push_back(this->cur);
                    consume();
                }
                consume();
                while (isalpha(this->cur)) {
                    add->r_name.push_back(this->cur);
                    consume();
                }
            }
            else if (this->buffer == "SUB") {
                auto* sub = new SubToken;
                sub->type = "SUB";
                this->tokens.push_back(sub);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    sub->l_name.push_back(this->cur);
                    consume();
                }
                consume();
                while (isalpha(this->cur)) {
                    sub->r_name.push_back(this->cur);
                    consume();
                }
            }
            else if (this->buffer == "MUL") {
                auto* mul = new MulToken;
                mul->type = "MUL";
                this->tokens.push_back(mul);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    mul->l_name.push_back(this->cur);
                    consume();
                }
                consume();
                while (isalpha(this->cur)) {
                    mul->r_name.push_back(this->cur);
                    consume();
                }
            }
            else if (this->buffer == "DIV") {
                auto* div = new DivToken;
                div->type = "DIV";
                this->tokens.push_back(div);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    div->l_name.push_back(this->cur);
                    consume();
                }
                consume();
                while (isalpha(this->cur)) {
                    div->r_name.push_back(this->cur);
                    consume();
                }
            }
            else if (this->buffer == "SAV") {
                auto* sav = new SaveToken;
                sav->type = "SAV";
                this->tokens.push_back(sav);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    sav->target_name.push_back(this->cur);
                    consume();
                }
            }
            else if (this->buffer == "PRT") {
                auto* print = new PrintToken;
                print->type = "PRT";
                this->tokens.push_back(print);
                this->buffer.clear();
                if (peek() != '\n') {
                    consume();
                    while (isalpha(this->cur)) {
                        print->target_name.push_back(this->cur);
                        consume();
                    }
                }
            }
            else if (this->buffer == "INC") {
                auto* inc = new IncToken;
                inc->type = "INC";
                this->tokens.push_back(inc);
                this->buffer.clear();
                consume();
                while (isalpha(this->cur)) {
                    inc->target_name.push_back(this->cur);
                    consume();
                }
            }
        }
        consume();
    }
}

void Tokenizer::clear_tokens() {
    for (auto token : tokens) {
        delete token;
    }
    this->tokens.clear();
}

void Tokenizer::read_file(const std::string& file_name) {
    std::ifstream file(file_name);
    std::stringstream stream;
    stream << file.rdbuf();
    this->input = stream.str();
    file.close();
}

void Tokenizer::print_tokens() {
    std::cout << "Tokens start" << std::endl;
    for (auto token: tokens) {
        std::cout << token->type << std::endl;
    }
    std::cout << "Tokens end" << std::endl;
}

char Tokenizer::peek() {
    size_t next = this->i + 1;
    return this->input[next];
}

bool Tokenizer::token_check() {
    if (this->tokens[0]->type != "STR") {
        std::cout << "Missing STR Token" << std::endl;
        return false;
    }
    else if (this->tokens[this->tokens.size()-1]->type != "END" ) {
        std::cout << "Misplaced or missing END Token" << std::endl;
        return false;
    }
    return true;
}

void Tokenizer::execute() {
    //Create a temporary value holder like the AC register.
    //Store the value in that said holder until it changes.
    auto temp = new IntToken;
    for (auto token: this->tokens) {
        if (token->type == "INT") {
            auto int_token = dynamic_cast<IntToken*>(token);
            this->storage.push_back(int_token);
        }
        else if (token->type == "ADD") {
            IntToken* t1 = nullptr;
            IntToken* t2 = nullptr;
            auto result_token = dynamic_cast<AddToken*>(token);
            for (auto stored_token: this->storage) {
                if (stored_token->name == result_token->l_name) {
                    t1 = stored_token;
                }
                else if (stored_token->name == result_token->r_name) {
                    t2 = stored_token;
                }
            }
            if (t1 && t2) {
                temp->value = t1->value + t2->value;
            }
        }
        else if (token->type == "SUB") {
            IntToken* t1 = nullptr;
            IntToken* t2 = nullptr;
            auto result_token = dynamic_cast<SubToken*>(token);
            for (auto stored_token: this->storage) {
                if (stored_token->name == result_token->l_name) {
                    t1 = stored_token;
                }
                else if (stored_token->name == result_token->r_name) {
                    t2 = stored_token;
                }
            }
            if (t1 && t2) {
                temp->value = t1->value - t2->value;
            }
        }
        else if (token->type == "MUL") {
            IntToken* t1 = nullptr;
            IntToken* t2 = nullptr;
            auto result_token = dynamic_cast<MulToken*>(token);
            for (auto stored_token: this->storage) {
                if (stored_token->name == result_token->l_name) {
                    t1 = stored_token;
                }
                else if (stored_token->name == result_token->r_name) {
                    t2 = stored_token;
                }
            }
            if (t1 && t2) {
                temp->value = t1->value * t2->value;
            }
        }
        else if (token->type == "DIV") {
            IntToken* t1 = nullptr;
            IntToken* t2 = nullptr;
            auto result_token = dynamic_cast<DivToken*>(token);
            for (auto stored_token: this->storage) {
                if (stored_token->name == result_token->l_name) {
                    t1 = stored_token;
                }
                else if (stored_token->name == result_token->r_name) {
                    t2 = stored_token;
                }
            }
            if (t1 && t2) {
                temp->value = t1->value / t2->value;
            }
        }
        else if (token->type == "SAV") {
            bool var_found = false;
            auto *save_token = dynamic_cast<SaveToken *>(token);
            for (auto stored_token: this->storage) {
                if (stored_token->name == save_token->target_name) {
                    var_found = true;
                }
            }
            if (!var_found) {
                auto *new_token = new IntToken;
                new_token->value = temp->value;
                new_token->name = save_token->target_name;
                new_token->heapAllocated = true;
                this->storage.push_back(new_token);
            }
        }
        else if (token->type == "PRT") {
            bool value_found = false;
            auto print_token = dynamic_cast<PrintToken*>(token);
            std::cout << "Output: ";
            for (auto stored_token: storage) {
                if (stored_token->name == print_token->target_name) {
                    value_found = true;
                    std::cout << stored_token->value << std::endl;
                }
            }
            if (!value_found) {
                std::cout << "NULL" << std::endl;
            }
        }
        else if (token->type == "INC") {
            bool value_found = false;
            auto inc_token = dynamic_cast<IncToken*>(token);
            std::cout << "Target Name: " << inc_token->target_name << std::endl;
            for (auto stored_token: storage) {
                if (stored_token->name == inc_token->target_name) {
                    value_found = true;
                    stored_token->value += 1;
                }
            }
            if (!value_found) {
                std::cout << "Cannot increment " << inc_token->target_name << " target not found" << std::endl;
            }
        }
    }
    delete temp;
}

void Tokenizer::clear_storage() {
    for (auto token: this->storage) {
        if (token->heapAllocated) delete token;
    }
    this->storage.clear();
}

void Tokenizer::print_storage() {
    std::cout << "Storage start" << std::endl;
    for (auto token: this->storage) {
        if (!token->name.empty() && token->value) {
            std::cout << "Token name: " << token->name << " value: " << token->value << std::endl;
        }
    }
    std::cout << "Storage end" << std::endl;
}


