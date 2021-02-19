//
// Created by student on 2019-08-30.
//

#ifndef LAB01_2_TAGPARSER_HPP
#define LAB01_2_TAGPARSER_HPP

#include <string>
#include <vector>
#include "Tokenizer.hpp"
#include <map>

class TagParser {
    struct TokenPair{
        Token open, close;
    };

public:
    TagParser(std::string);
    void Parse();
    void handleOpenTag(Tokenizer& tokenizer, Token& token);
    void handleCloseTag(Tokenizer& tokenizer, Token& token);



private:
    std::string inputFileName;
    std::vector<Token> openTagStack;
    std::map<std::string,std::vector<TokenPair>> tagMap;

};


#endif //LAB01_2_TAGPARSER_HPP
