//
// Created by Ali A. Kooshesh on 8/21/18.
//

#include <iostream>
#include "Tokenizer.hpp"

Tokenizer::Tokenizer(std::string name): lineNumber{1},
                                        charPosition{1},
                                        prevToken{0, 0},
                                        inputFileName{name}{
    inputStream.open(inputFileName, std::ios::in);  // open the input file. We will make sure that it is open in getToken.
}

bool Tokenizer::charOfInterest(char c) {
    // is c the initial (or the sole) character of a token?
    if (c == '<' || c == '>' || (c == '/' && inputStream.peek() == '>')) {
        return true;
    }
    return false;
    // you need to replace this with code that compares c with characters like '<', '>', etc.
}

Token Tokenizer::returnToken(Token token){
    hasgotten = true;
    prevToken = token;
    std::cout << hasgotten;
}

Token Tokenizer::getToken() {
    char c;
    std::cout << prevToken.tagName();
    if(hasgotten){
        std::cout << "returned prevToken";
        hasgotten = false;
        return prevToken;
    }

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }



    while( inputStream.get(c) && ! charOfInterest(c) ) {
        charPosition++;
        if (c == '\n') {
            lineNumber++;
        }
        //check for character here
        //if (c ==)
        // keep track of the line number and the character position
    }

    Token token(lineNumber, charPosition);

    if( inputStream.eof() ) {
        token.endOfFile() = true;
        return token;
    }

    if( c == '<' ) { // A possible open tag.
        std::string tagName;
        token.isOpenTag() = true;
        token.isOpenAngleBracket() = true;
        //tagName += c;
        charPosition++;
        // suppose we have found an open em-tag.
        if (inputStream.peek() == '/') {
            inputStream.get(c);
            charPosition ++;
            //tagName += c;
            token.isOpenTag() = false;
            token.isCloseTag() = true;
            //token.makeCloseTag(tagName);
        }
        //std::cout << char(inputStream.peek());
        while(isalnum(inputStream.peek()) && inputStream.get(c)) {
            //inputStream.get(c);
            //inputStream.peek();
            tagName += c;
            charPosition++;
        }
        if (token.isOpenTag()) {
            token.makeOpenTag(tagName);
        }
        else if(token.isCloseTag()) {
            token.makeCloseTag(tagName);
        }
        return token;
    }
    else if( c == '/' ) {
        std::string tagName;
        charPosition++;
        //inputStream.get(c);
        //charPosition++;
        if (inputStream.peek() == '>') {
            inputStream.get(c);
            charPosition++;
            tagName += c;
            token.isCloseStandAloneTag() = true;
            token.tagName() = tagName;
        }
    }
    else if (c == '>'){
        std::string tagName;
        charPosition++;
        tagName += c;
        token.isCloseAngleBracket() = true;
        tagName = ">";
        token.tagName() = tagName;

        return token;
    }
    else
        charPosition++;
    //charPosition++;
        // ... more if-else statements here.

    //std::cout << charPosition;
    return token;
}


