#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define STRINGIFY(x) #x
 
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

enum TokenType {
    NUMERAL_TOK,
    STRING_TOK,
    CHAR_TOK,
    OPERATOR_TOK,
    KEYWORD_TOK,
    IDENTIFIER_TOK,
    SEPARATOR_TOK,
    SEMICOLON_TOK,
    INVALID_TOK
}; 



class Token {
    private:
        TokenType type;
        string tok;

    public:
        Token(TokenType t, string s) {
            type = t;
            tok = s;
        }
        string getType() {
            switch (type){
                case NUMERAL_TOK: return STRINGIFY(NUMERAL_TOK);
                case STRING_TOK: return STRINGIFY(STRING_TOK);
                case CHAR_TOK: return STRINGIFY(CHAR_TOK);
                // case CONSTANT_TOK: return STRINGIFY(CONSTANT_TOK);
                case OPERATOR_TOK: return STRINGIFY(OPERATOR_TOK);
                case KEYWORD_TOK: return STRINGIFY(KEYWORD_TOK);
                case IDENTIFIER_TOK: return STRINGIFY(IDENTIFIER_TOK);
                case SEPARATOR_TOK: return STRINGIFY(SEPARATOR_TOK);
                case SEMICOLON_TOK: return STRINGIFY(SEMICOLON_TOK);
                case INVALID_TOK: return STRINGIFY(INVALID_TOK);
            }
        }

        string getToken() {
            return tok;
        }
};

bool isNum(char c) {
    if (c >= ASCII_NUM_FIRST && c <= ASCII_NUM_LAST) return true;
    return false;
}

bool isAlpha(char c) {
    if (c >= ASCII_ALPHA_UPPERCASE_FIRST && c <= ASCII_ALPHA_UPPERCASE_LAST ||
        c >= ASCII_ALPHA_LOWERCASE_FIRST && c <= ASCII_ALPHA_LOWERCASE_LAST) return true;
    return false;
}

bool isWhitespace(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
            return true;
        default:
            return false;
    }
}

bool isSeparator(char c) {
    switch (c) {
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case '<':
        case '>':
        case EOF:
        return true;

        default:
        return false;
    }

    return false;
}

bool isOperator(char c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
        return true;
    
    default:
        return false;
    }
}

bool isTokNumeral(string tok) {

    for (int i = 0; i < tok.length(); i++) {

        if (!isNum(tok.at(i)) && tok.at(i) != '.') return false;
    }
    return true;
}
bool isTokOperator(string tok) {
    if (tok.length() == 1 && isOperator(tok.at(0))) return true;
    return false;
}
bool isTokKeyword(string tok) {
    if (tok == "if" || tok == "else" || tok == "for" || tok == "while" ||
        tok == "int" || tok == "char" || tok == "bool" || tok == "true" || 
        tok == "false" || tok == "double" || tok == "string"
    ) return true;
    return false;
}
bool isTokIdentifier(string tok) {
    if (isNum(tok.at(0)) || 
        isTokKeyword(tok) || 
        tok.at(0) == '\'' // Is CHAR_TOK
    ) return false;

    for (int i = 0; i < tok.length(); i++) {
        if (isOperator(tok.at(i)) || isSeparator(tok.at(i))) return false;
    } 
    return true;
}
bool isTokSeparator(string tok) {
    if (tok.length() == 1 && isSeparator(tok.at(0))) return true;
    return false;
}
bool isTokSemicolon(string tok) {
    if (tok.length() == 1 && tok.at(0) == ';') return true;
    return false;
}
bool isTokCharLiteral(string tok) {
    if (tok.length() != 3 && // "\'h\'".length() == 3 -> true
        tok.at(0) != '\'' && 
        tok.at(2) != '\'' && 
        tok.at(1) < ASCII_PRINTABLE_FIRST && (
            ((u_int8_t) tok.at(1)) == ASCII_UNUSED_1 ||
            ((u_int8_t) tok.at(1)) == ASCII_UNUSED_2 || 
            ((u_int8_t) tok.at(1)) == ASCII_UNUSED_3 || 
            ((u_int8_t) tok.at(1)) == ASCII_UNUSED_4 || 
            ((u_int8_t) tok.at(1)) == ASCII_UNUSED_5
        )
    ) {return false;} 
    return true;
}
TokenType categorize(string tok) {

    if (isTokSemicolon(tok)) return SEMICOLON_TOK;
    else if (isTokSeparator(tok)) return SEPARATOR_TOK;
    else if (isTokOperator(tok)) return OPERATOR_TOK;
    else if (isTokNumeral(tok)) return NUMERAL_TOK; // TODO
    else if (isTokKeyword(tok)) return KEYWORD_TOK;
    else if (isTokIdentifier(tok)) return IDENTIFIER_TOK;
    else if (isTokCharLiteral(tok)) return CHAR_TOK;

    cout << "Invalid token: " << tok << endl;
    return INVALID_TOK;
}

int main(int argc, char **argv) {

    // Define lambdas
    auto flushTok = [] (string &tok, vector<string> &toks) {
        if (tok.length() > 0) {
            toks.push_back(tok);
            tok = "";
        }
    };
    auto handleSingleCharTok = [flushTok] (char &c, string &tok, vector<string> &toks) {

        flushTok(tok, toks); // Flush curr tok buff if not empty
        tok.push_back(c); // Add and flush new separator tok
        flushTok(tok, toks);
    };
    auto handleCharLiteral = [flushTok] (ifstream &f, string &tok, vector<string> &toks) {
        if (tok.length() > 0) {
            cerr << "Error in HandleCharLiteral: Token buffer should be empty" << endl; // Temporary
            exit(1);
        }

        tok = "";
        char ch = f.get();
        tok.push_back(ch);

        while ((ch = f.get()) && ch != EOF) {
            tok.push_back(ch);
            if (ch == '\'') break;
        }
        flushTok(tok, toks);
    };


    
    ifstream f("test.kal");
    string tok;
    char c;
    vector<string> toks;
    
   

    while ((c = f.peek()/* f.get() */)) {
        if (c == EOF) { // Flush last token
            flushTok(tok, toks);
            break;
        }


        if (c == '\'') {
            handleCharLiteral(f, tok, toks);
        } else if (isSeparator(c) || isOperator(c) || c == ';') {
            handleSingleCharTok(c, tok, toks);

        } else if(!isWhitespace(c)) {  // general case
            tok.push_back(c);

        } else { // Flush tok
            flushTok(tok, toks);
        }


        if (f.peek() != EOF) {
            f.seekg(1, fstream::cur);
        } else {
            break;
        }
    }
    f.close();

    vector<Token> lexemes;
    for (int i = 0; i < toks.size(); i++) {
        lexemes.push_back(Token(categorize(toks.at(i)), toks.at(i)));
    }
    for (int i = 0; i < lexemes.size(); i++) {
        cout << lexemes.at(i).getType() << ": " << "<" << lexemes.at(i).getToken() << ">" << endl;

    }
    return 0;
}