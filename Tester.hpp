#ifndef TESTER_H
#define TESTER_H

#include <string>
#include <vector>
#include "Token.hpp"
#include "Lexer.hpp"

#define TEST_VERBOSE 0b00000001

#define TEST0 0
#define TEST1 1
#define TEST2 2
#define TEST3 3
#define TEST4 4

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

    // Lexer lexer = Lexer();
    std::vector<Token> outToks;


    void printError(int i, int j, ErrorType errT);

    public:
    void setup();
    void setup(u_int8_t inputFlags);
    void selectUnits(std::vector<int> units);
    std::vector<int> getSelectedIdxs() {return selectedIndices;}
    std::vector<TestUnit> getTUnits() {return tUnits;}
    void run();
};

#endif