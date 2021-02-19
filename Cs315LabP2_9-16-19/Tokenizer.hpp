//
// Created by Ali A. Kooshesh on 8/21/18.
//

#ifndef LAB01_2_TOKENIZER_HPP
#define LAB01_2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();
    Token returnToken(Token token);

private:
    int lineNumber, charPosition;
    std::string inputFileName;
    std::ifstream inputStream;
    bool hasgotten = false;
    Token prevToken;
    bool charOfInterest(char c);
};


#endif //LAB01_2_TOKENIZER_HPP
