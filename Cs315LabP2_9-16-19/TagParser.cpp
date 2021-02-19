2//
// Created by student on 2019-08-30.
//

#include "TagParser.hpp"
#include <iostream>
#include <vector>


TagParser::TagParser(std::string name): inputFileName{name} {};



void TagParser::Parse() {
    Tokenizer tokenizer(inputFileName);
    Token token = tokenizer.getToken();
    while (!token.endOfFile()) {
        if (token.isOpenTag()) {
            handleOpenTag(tokenizer, token);
        }
        else if (token.isCloseTag()) {
            handleCloseTag(tokenizer, token);
//            else if (token.isStandAloneCloseTag()) // maybe not use
//                handleStandAloneCloseTag(token);
        }
        else if (token.isCloseAngleBracket() ||token.isOpenAngleBracket()) { // create new type for token as openAngleBracket
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                      : " ignoring random open angle-bracket.") << std::endl;
        }
        else {
            token.print();
        }
        token = tokenizer.getToken();
    }
    std::cout << "The following is a list of well-formed HTML tags.\n\n";
    for (auto mapIter : tagMap) {
        // our map, pairs an array of Tokens with tag-name strings.
        std::cout << mapIter.first << " appeared in the following " << mapIter.second.size() << "locations.\n";
        for(auto vIter : mapIter.second){
            std::cout << "    ";
            vIter.open.print();
            std::cout << " -- ";
            vIter.close.print();
            std::cout << "\n";
        }
    }
}
void TagParser::handleOpenTag(Tokenizer &tokenizer, Token &token) {
    Token nextToken = tokenizer.getToken();
    if (nextToken.isCloseAngleBracket()) {
        openTagStack.push_back(token);
    } else if (nextToken.isCloseStandAloneTag()) {
        tagMap[token.tagName()].push_back({{token},{nextToken}});
        //tokenizer.returnToken(nextToken);
    }
    else {
        std::cout << "<" << token.tagName() << " is missing a '>' or '/>'. Will discard it.";
        tokenizer.returnToken(nextToken);
    }
    //if (token.isOpenAngleBracket()){
    //}
    //check for well formed tags
}

void TagParser::handleCloseTag(Tokenizer& tokenizer, Token& token){
    Token nextToken = tokenizer.getToken();
    if (nextToken.isCloseAngleBracket()) {
        if (openTagStack.back().tagName() == token.tagName()) {
            tagMap[token.tagName()].push_back({{openTagStack.back()},
                                               {token}});
            openTagStack.pop_back();
        }
        else {
            for (int i = 0; i < openTagStack.size(); i++){
                if (openTagStack[i].tagName() == token.tagName()){
                    token.print();
                    std::cout << " closes while the following tags remain open.\n    ";
                    int tagListStart = i;
                    for (int n = tagListStart; n < openTagStack.size(); n++) {
                        openTagStack[n].print();
                    }
                    openTagStack.erase(openTagStack.begin() + i-1);
                }
                else{
                    token.print();
                    std::cout << " (with close angle bracket ";
                    nextToken.print();
                    std::cout << ") doesn't have a\nmatching open tag.Will discard.";
                }
            }

        }
    }
}
