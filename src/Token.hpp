#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "FilePosition.hpp"

#define STRINGIFY(x) #x


enum TokenType {
    INTEGER_TOK,
    FLOAT_TOK,
    STRING_TOK,
    CHAR_TOK,
    OPERATOR_TOK,
    DOUBLE_OPERATOR_TOK,
    KEYWORD_TOK,
    IDENTIFIER_TOK,
    SEPARATOR_TOK,
    SEMICOLON_TOK,
    INVALID_TOK
}; 


class Token {
    private:
        TokenType type;
        std::string tok;
        FilePosition pos;

    public:
        Token(TokenType t, std::string s, FilePosition position);
        std::string getType();
        std::string getToken() {return tok;}
        FilePosition getPos() {return pos;}
        std::string toString();
        bool operator==(Token rhs);
        bool operator!=(Token rhs);
        
};

#endif