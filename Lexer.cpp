#include "Lexer.hpp"

bool Lexer::isNum(char c) {
    if (c >= ASCII_NUM_FIRST && c <= ASCII_NUM_LAST) return true;
    return false;
}

bool Lexer::isAlpha(char c) {
    if ((c >= ASCII_ALPHA_UPPERCASE_FIRST && c <= ASCII_ALPHA_UPPERCASE_LAST) ||
        (c >= ASCII_ALPHA_LOWERCASE_FIRST && c <= ASCII_ALPHA_LOWERCASE_LAST)) return true;
    return false;
}

bool Lexer::isWhitespace(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
            return true;
        default:
            return false;
    }
}

bool Lexer::isSeparator(char c) {
    switch (c) {
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case EOF:
        return true;

        default:
        return false;
    }

    return false;
}

bool Lexer::isOperator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '<':
        case '>':
        case '^':
        case '!':
        case '&':
        case '|':
        case '?':
        return true;
        
        default:
        return false;
    }
}

void Lexer::flushTok(std::vector<Token> &lexes, std::string &tok, FilePosition &pos) {
    if (tok.length() > 0) {
        lexes.push_back(
            Token(categorize(tok), 
            tok, 
            FilePosition(pos.getLine(), pos.getCol() - tok.length()))
        );
        tok = "";
    }
}

void Lexer::handleSingleCharTok(char &c, std::string &tok, std::vector<Token> &lexes, FilePosition &pos){

    flushTok(lexes, tok, pos); // Flush curr tok buff if not empty
    tok.push_back(c); // Add and flush new separator tok
    flushTok(lexes, tok, pos);
};

void Lexer::handleCharLiteral(std::ifstream &f, std::string &tok, std::vector<Token> &lexes, FilePosition &pos) {
    if (tok.length() > 0) { // Temporary
        std::cerr << "Error in HandleCharLiteral: Token buffer should be empty" << std::endl; 
        exit(1);
    }

    tok = "";
    char ch = f.get();
    tok.push_back(ch);

    while ((ch = f.get())) {
        tok.push_back(ch);
        if (ch == '\'') break;
        if (ch == EOF) {
            std::cout << "Error unmatched single quote in char literal" << std::endl;
            exit(2);
        }
    }
    flushTok(lexes, tok, pos);
    f.seekg(-1, std::fstream::cur);
}

void Lexer::handleStringLiteral(std::ifstream &f, std::string &tok, std::vector<Token> &lexes, FilePosition &pos) {
    if (tok.length() > 0) { // Temporary
        std::cerr << "Error in HandleStringLiteral: Token buffer should be empty: Previous token is incorrect." << std::endl; 
        exit(1);
    }

    tok = "";
    char ch = f.get();
    tok.push_back(ch);

    while ((ch = f.get())) {
        tok.push_back(ch);
        pos++;
        if (ch == '\"') break;
        if (ch == EOF) {
            std::cout << "Error unmatched double quote in string literal" << std::endl;
            exit(2);
        }
    }
    flushTok(lexes, tok, pos);
    f.seekg(-1, std::fstream::cur);
};
    
void Lexer::handleOperator(std::ifstream &f, std::string &tok, std::vector<Token> &toks, char &ch, FilePosition &pos) {
    flushTok(toks, tok, pos);
    tok.push_back(ch);
    f.seekg(1, std::fstream::cur);
    ch = f.peek();

    if (isOperator(ch)) { // Double Operator Token
        tok.push_back(ch);
        flushTok(toks, tok, pos);
    }
    else { // Single Operator Token
        flushTok(toks, tok, pos);
        f.seekg(-1, std::fstream::cur);
    }
}

bool Lexer::isTokInteger(std::string tok) {
    for (int i = 0; i < tok.length(); i++) {
        if (!isNum(tok.at(i))) return false;
    }
    return true;
}
bool Lexer::isTokFloat(std::string tok) {
    for (int i = 0; i < tok.length(); i++) {
        if (!isNum(tok.at(i)) && tok.at(i) != '.') return false;
    }
    return true;
}
bool Lexer::isTokOperator(std::string tok) {
    if (tok.length() == 1 && isOperator(tok.at(0))) return true;
    return false;
}
bool Lexer::isTokKeyword(std::string tok) {
    if (tok == "if"     || tok == "else"    || tok == "for"    || tok == "while"  ||
        tok == "int"    || tok == "char"    || tok == "bool"   || tok == "true"   || 
        tok == "false"  || tok == "double"  || tok == "string" || tok == "return" ||
        tok == "public" || tok == "private" || tok == "long"   || tok == "short"  ||
        tok == "void"
    ) return true;
    return false;
}
bool Lexer::isTokIdentifier(std::string tok) {
    if (isNum(tok.at(0)) || 
        isTokKeyword(tok) || 
        tok.at(0) == '\'' || // Is CHAR_TOK
        tok.at(0) == '\"'   // Is STRING_TOK
    ) return false;

    for (int i = 0; i < tok.length(); i++) {
        if (isOperator(tok.at(i)) || isSeparator(tok.at(i))) return false;
    } 
    return true;
}
bool Lexer::isTokSeparator(std::string tok) {
    if (tok.length() == 1 && isSeparator(tok.at(0))) return true;
    return false;
}
bool Lexer::isTokSemicolon(std::string tok) {
    if (tok.length() == 1 && tok.at(0) == ';') return true;
    return false;
}
bool Lexer::isTokCharLiteral(std::string tok) {
    if (tok.length() == 3 &&
        tok.at(0) == '\'' &&
        tok.at(2) == '\'' &&
        tok.at(1) >= ASCII_PRINTABLE_FIRST && 
        ((u_int8_t) tok.at(1)) != ASCII_UNUSED_1 &&
        ((u_int8_t) tok.at(1)) != ASCII_UNUSED_2 && 
        ((u_int8_t) tok.at(1)) != ASCII_UNUSED_3 && 
        ((u_int8_t) tok.at(1)) != ASCII_UNUSED_4 && 
        ((u_int8_t) tok.at(1)) != ASCII_UNUSED_5
    ) return true;
    return false;
}
bool Lexer::isTokStringLiteral(std::string tok) {
    if (tok.length() < 2 ||
        tok.at(0) != '\"' ||
        tok.at(tok.length() - 1) != '\"'
    ) return false;
    return true;
}
/* Possible operators: 
    Ideas: := # @ $ % \ : ~ +? -? *? /? =? <? >? ^? @? :~ ~: =~ ** <...> 
*/
bool Lexer::isTokDoubleOperator(std::string tok) {
    
    if (tok.length() != 2) return false;
    if (tok != "==" &&
        tok != "!=" && 
        tok != "+=" && 
        tok != "-=" && 
        tok != "*=" && 
        tok != "/=" && 
        tok != "&&" && 
        tok != "||" && 
        tok != "<<" && 
        tok != ">>" && 
        tok != "++" && 
        tok != "--"
    ) return false;
    return true;
}


TokenType Lexer::categorize(std::string tok) {
    
    // Order is imperative
    if (isTokSemicolon(tok))           return SEMICOLON_TOK;
    else if (isTokSeparator(tok))      return SEPARATOR_TOK;
    else if (isTokDoubleOperator(tok)) return DOUBLE_OPERATOR_TOK;
    else if (isTokOperator(tok))       return OPERATOR_TOK;
    else if (isTokInteger(tok))        return INTEGER_TOK;
    else if (isTokFloat(tok))          return FLOAT_TOK;
    else if (isTokKeyword(tok))        return KEYWORD_TOK;
    else if (isTokIdentifier(tok))     return IDENTIFIER_TOK;
    else if (isTokCharLiteral(tok))    return CHAR_TOK;
    else if (isTokStringLiteral(tok))  return STRING_TOK;

    std::cout << "Invalid token: " << tok << std::endl;
    return INVALID_TOK;
}



std::vector<Token> Lexer::tokenize(std::string filename) {

    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }
    std::string tok;
    char c;
    std::vector<std::string> toks;
    std::vector<Token> tokens;
    FilePosition curPos = FilePosition();



    c = f.peek();
    while (c) {
        if (c == '\'') {
            handleCharLiteral(f, tok, tokens, curPos);

        } else if (c == '\"') {
            handleStringLiteral(f, tok, tokens, curPos);

        } else if (isOperator(c)) {
            handleOperator(f, tok, tokens, c, curPos);

        } else if (isSeparator(c) || c == ';') {
            handleSingleCharTok(c, tok, tokens, curPos);

        } else if(!isWhitespace(c)) {  // general case
            tok.push_back(c);

        } else { // Flush tok in whitespace
            flushTok(tokens, tok, curPos);
        }


        // Next char
        f.seekg(1, std::fstream::cur);
        c = f.peek();
        curPos++;

        if (c != EOF) {
            if (c == '\n') {
                flushTok(tokens, tok, curPos);
                curPos.newLine();
            }

        } else { // EOF: Flush last token
            flushTok(tokens, tok, curPos);
            break;
        }
    }

    f.close();
    
    return tokens;
}