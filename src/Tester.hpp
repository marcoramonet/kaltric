#ifndef TESTER_H
#define TESTER_H

#include <string>
#include <vector>
#include "Token.hpp"
#include "Lexer.hpp"
#define TEST_VERBOSE 0b00000001

enum ErrorType {
TOK_TYPE,
TOK_VAL, 
TOK_POS
};


class TestUnit {
    public:
    std::string filename;
    std::vector<Token> toks;
    TestUnit(std::string f, std::vector<Token> ts) {
        filename = f;
        toks = ts;
    }
};

class Tester {

    private:
    std::vector<TestUnit> tUnits;
    u_int8_t flags = 0b00000000;
    std::vector<int> selectedIndices = {};

    Lexer lexer = Lexer();
    std::vector<Token> outToks;


    void printError(int i, int j, ErrorType errT);

    public:
    void setup();
    void setup(u_int8_t fl);
    void setSelectedUnits(std::vector<int> units);
    std::vector<int> getSelected() {return selectedIndices;}
    void run();
};

#endif