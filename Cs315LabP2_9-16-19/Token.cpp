//
// Created by Ali A. Kooshesh on 8/21/18.
//

#include <iostream>
#include <iomanip>
#include "Token.hpp"

Token::Token(int line, int pos): _isOpenTag{false},
                                 _isCloseTag{false},
                                 _isCloseAngleBracket{false},
                                 _isCloseStandAloneTag{false},
                                 _isOpenAngleBracket{false},
                                 _eof{false},
                                 _tagName{""},
                                 _lineNumber{line},
                                 _charPos{pos} {}

bool &Token::isOpenTag() { return _isOpenTag; }
bool &Token::isCloseTag() { return _isCloseTag; }

bool &Token::isCloseAngleBracket() { return _isCloseAngleBracket; }
bool &Token::isOpenAngleBracket() { return _isOpenAngleBracket; }


bool &Token::endOfFile() { return _eof; }
bool &Token::isCloseStandAloneTag() { return _isCloseStandAloneTag; }

std::string Token::tagName() { return _tagName; }

void Token::makeOpenTag(std::string name) {
    _tagName = name;
    isOpenTag() = true;
}

void Token::makeCloseTag(std::string name) {
    _tagName = name;
    isCloseTag() = true;
}

void Token::print() {
    //std::cout << "[" << std::setw(2) << _lineNumber << ", " <<  std::setw(3) << _charPos << "] ";

    if(isOpenTag()) {
        std::cout << "[" << _lineNumber << ", " << _charPos << "] " << "<" << tagName();
    }
    else if(isCloseStandAloneTag()) {
        std::cout << "[" << _lineNumber << ", " << _charPos << "] " << "/>" << std::endl;
    }
    else if(isCloseTag()){
        std::cout << "[" << _lineNumber << ", " << _charPos << "] " << "</" << tagName() << std::endl;
    }
    else if(isCloseAngleBracket()){
        std::cout << "[" << _lineNumber << ", " << _charPos << "] " << ">" << tagName() << std::endl;
    }
    // ...
}
