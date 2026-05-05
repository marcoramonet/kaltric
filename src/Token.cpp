#include "Token.hpp"


Token::Token(TokenType t, std::string s, FilePosition position) {
    Token::type = t;
    Token::tok = s;
    Token::pos = position;
}


std::string Token::getType() {
    switch (Token::type){
        case INTEGER_TOK: return STRINGIFY(INTEGER_TOK);
        case FLOAT_TOK: return STRINGIFY(FLOAT_TOK);
        case STRING_TOK: return STRINGIFY(STRING_TOK);
        case CHAR_TOK: return STRINGIFY(CHAR_TOK);
        case OPERATOR_TOK: return STRINGIFY(OPERATOR_TOK);
        case DOUBLE_OPERATOR_TOK: return STRINGIFY(DOUBLE_OPERATOR_TOK);
        case KEYWORD_TOK: return STRINGIFY(KEYWORD_TOK);
        case IDENTIFIER_TOK: return STRINGIFY(IDENTIFIER_TOK);
        case SEPARATOR_TOK: return STRINGIFY(SEPARATOR_TOK);
        case SEMICOLON_TOK: return STRINGIFY(SEMICOLON_TOK);
        case INVALID_TOK: return STRINGIFY(INVALID_TOK);
    }
}

std::string Token::toString() {
            std::stringstream ss;
            ss << Token::pos.toString() << ": " << Token::getType() << ": " << "<" << Token::tok << ">";
            return ss.str();
        }

bool Token::operator==(Token rhs) {
    if (Token::getType() == rhs.getType() &&
        Token::getToken() == rhs.getToken()
    ) return true;
    return false;
}
bool Token::operator!=(Token rhs) {
        if (Token::getType() != rhs.getType() ||
        Token::getToken() != rhs.getToken()
    ) return true;
    return false;
}