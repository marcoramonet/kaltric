#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Token.hpp"
#include "FilePosition.hpp"

#define ASCII_NUM_FIRST 48
#define ASCII_NUM_LAST 57
#define ASCII_ALPHA_LOWERCASE_FIRST 97
#define ASCII_ALPHA_LOWERCASE_LAST 122
#define ASCII_ALPHA_UPPERCASE_FIRST 65
#define ASCII_ALPHA_UPPERCASE_LAST 90
#define ASCII_PRINTABLE_FIRST 32
#define ASCII_UNUSED_1 129
#define ASCII_UNUSED_2 141
#define ASCII_UNUSED_3 143
#define ASCII_UNUSED_4 144
#define ASCII_UNUSED_5 157


class Lexer {
    public:
    bool isNum(char c);
    bool isAlpha(char c);
    bool isWhitespace(char c);
    bool isSeparator(char c);
    bool isOperator(char c);
    
    bool isTokInteger(std::string tok);
    bool isTokFloat(std::string tok);
    bool isTokOperator(std::string tok);
    bool isTokKeyword(std::string tok);
    bool isTokIdentifier(std::string tok);
    bool isTokSeparator(std::string tok);
    bool isTokSemicolon(std::string tok);
    bool isTokCharLiteral(std::string tok);
    bool isTokStringLiteral(std::string tok);
    bool isTokDoubleOperator(std::string tok);
    TokenType categorize(std::string tok);


    
    void flushTok(std::vector<Token> &lexes, std::string &tok, FilePosition &pos);
    void handleSingleCharTok(char &c, std::string &tok, std::vector<Token> &lexes, FilePosition &pos);
    void handleCharLiteral(std::ifstream &f, std::string &tok, std::vector<Token> &lexes, FilePosition &pos);
    void handleStringLiteral(std::ifstream &f, std::string &tok, std::vector<Token> &lexes, FilePosition &pos);
    void handleOperator(std::ifstream &f, std::string &tok, std::vector<Token> &lexes, char &ch, FilePosition &pos);
    
    std::vector<Token> tokenize(std::string filename);
};
                                            
#endif



