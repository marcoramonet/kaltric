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


class LexState {
    public:
    std::ifstream file;
    std::vector<Token> tokens;
    std::string tokBuf;
    FilePosition currPos;
    char c;
    bool valid = false;

    LexState();
    LexState(std::string filePath);

    std::string toString();
};

class Lexer {

    private:
    LexState state;
    
    /**
     * State dependent functions used in tokenize()
     */
    void flushTok();
    void handleSingleCharTok();
    void handleCharLiteral();
    void handleStringLiteral();
    void handleOperator();
    bool loopLogic();
    
    public:
    Lexer() : state() {}
    Lexer(std::string filePath) : state(filePath) {}

    /*
    Helper functions. State independent.
    */
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
    
    /**
      * Main interface.
      */
    TokenType categorize(std::string tok); // State independent
    std::vector<Token> tokenize(); // State dependent
    std::vector<Token> tokenize(std::string filename); // State dependent
};
                                            
#endif