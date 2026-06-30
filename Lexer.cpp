#include "Lexer.hpp"
#include "utils.hpp"


/*------------------------------------------LEX STATE------------------------------------------*/
LexState::LexState() {
    tokBuf = "";
    c = EOF;
    tokens = {};
    currPos = FilePosition();
    valid = false;
}
LexState::LexState(std::string filePath) : file(filePath) {
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        valid = false;
    } else {
        tokBuf = "";
        c = EOF;
        tokens = {};
        currPos = FilePosition();
        valid = true; 
    }
}
std::string LexState::toString() {
    std::stringstream ss;
    ss << valid << "\n" << 
    "Tokens: " << "\n";

    for (int i = 0; i < tokens.size(); i++) {
        ss << "\t" << tokens.at(i).toString() << "\n";
    }

    ss << "tokBuf: " << tokBuf << "\n";

    ss << "currPos: " << currPos.toString() << "\n" <<
    "c: " << c << "\n";

    return ss.str();
}

/*------------------------------------------LEXER------------------------------------------*/
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
void Lexer::consume() {
    state.file.seekg(1, std::fstream::cur);
    state.c = state.file.peek();
    state.currPos++;
}
void Lexer::flushTok() {
    if (state.tokBuf.length() > 0) {
        state.tokens.push_back(
            Token(
                categorize(state.tokBuf), 
                state.tokBuf, 
                FilePosition(state.currPos.getLine(), state.currPos.getCol() - state.tokBuf.length())
            )
        );
        state.tokBuf = "";
    }
}
void Lexer::flushTok(FilePosition pos) {
    if (state.tokBuf.length() > 0) {
        state.tokens.push_back(
            Token(
                categorize(state.tokBuf), 
                state.tokBuf, 
                pos
            )
        );
        state.tokBuf = "";
    }
}
void Lexer::handleSeparatorTok(){
    flushTok();
    state.tokBuf.push_back(state.c);
    flushTok(state.currPos);
}
void Lexer::handleCharLiteral() {
    if (state.tokBuf.length() > 0) { // Temporary
        std::cerr << "Error in HandleCharLiteral: Token buffer should be empty" << std::endl; 
        exit(1);
    }

    state.tokBuf = "";
    // char ch = s.file.get();
    char ch = state.file.get();
    state.tokBuf.push_back(ch);

    while ((ch = state.file.get())) {
        state.tokBuf.push_back(ch);
        if (ch == '\'') break;
        if (ch == EOF) {
            std::cout << "Error unmatched single quote in char literal" << std::endl;
            exit(2);
        }
    }
    flushTok();
    state.file.seekg(-1, std::fstream::cur);
}
void Lexer::handleStringLiteral() {
    if (state.tokBuf.length() > 0) { // Temporary
        std::cerr << "Error in HandleStringLiteral: Token buffer should be empty: Previous token is incorrect." << std::endl; 
        exit(1);
    }

    state.tokBuf = "";
    char ch = state.file.get();
    state.tokBuf.push_back(ch);

    while ((ch = state.file.get())) {
        state.tokBuf.push_back(ch);
        state.currPos++;
        if (ch == '\"') break;
        if (ch == EOF) {
            std::cout << "Error unmatched double quote in string literal" << std::endl;
            exit(2);
        }
    }
    flushTok();
    state.file.seekg(-1, std::fstream::cur);
}; 

void Lexer::handleSingleOperator() {
    flushTok();
    state.tokBuf.push_back(state.c);
    flushTok(state.currPos);
}
void Lexer::handleDoubleOperator(std::string doubleOp) {
    state.tokBuf.append(doubleOp);
    flushTok(state.currPos);
    state.currPos++;
}
void Lexer::handleOperator() {

    flushTok();

    std::string tmp = "";

    tmp.push_back(state.c);

    state.file.seekg(1, std::fstream::cur);
    state.c = state.file.peek();
    
    if (isOperator(state.c)) {
        tmp.push_back(state.c);
        if (isTokDoubleOperator(tmp)) {
            handleDoubleOperator(tmp);
            return;
        }
    }
    // reset and do single
    state.file.seekg(-1, std::fstream::cur);
    state.c = state.file.peek();
    handleSingleOperator();
}
void Lexer::handleWhiteSpace() {
    flushTok();
    if (state.c == '\n') state.currPos.newLine();
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
    if (tok.length() == 0 ||
        isNum(tok.at(0))  || 
        tok.at(0) == '\'' || // Is CHAR_TOK
        tok.at(0) == '\"' || // Is STRING_TOK
        isTokKeyword(tok)
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
bool Lexer::checkNHandleEOF() {
    if (!state.file.eof()) 
        return true;
    else {
        flushTok();
        return false;
    }
}
std::vector<Token> Lexer::tokenize(std::string filename) {
    
    state = LexState(filename);

    if (!state.valid) {
        std::cerr << "\033[1;31mError\033[0m: Attempting to tokenize with invalid lexer state. Check file validity." << std::endl;
        return {}; 
    }

    state.c = state.file.peek();

    while (checkNHandleEOF()) {
        
        if (state.c == '\'') {
            handleCharLiteral();
            
        } else if (state.c == '\"') {
            handleStringLiteral();
            
        } else if (isOperator(state.c)) {
            handleOperator();
            
        } else if (isSeparator(state.c) || state.c == ';') {
            handleSeparatorTok();
            
        } else if(isAlpha(state.c) || isNum(state.c)) {  // general case: identifier number literal
            state.tokBuf.push_back(state.c);
            
        } else if (isWhitespace(state.c)) {
            handleWhiteSpace();
            
        } else {
            std::cerr << "\033[1;31mError\033[0m Character " << state.c << " not supported." << std::endl;
        }

        // std::cout << state.toString() << std::endl;

        consume();
    }

    state.file.close();
    
    return state.tokens;
}