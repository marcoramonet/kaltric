#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "Tester.hpp"
#include "Token.hpp"
#include "Lexer.hpp"

void Tester::setup(){
    Tester::tUnits.push_back(
        TestUnit(
            "testFiles/test0.kal",
            std::vector<Token>({
                Token(KEYWORD_TOK,   "int", {1,1}),
                Token(IDENTIFIER_TOK, "x", {1,5}),
                Token(OPERATOR_TOK,   "=", {1,7}),
                Token(SEPARATOR_TOK,  "(", {1,9}),
                Token(INTEGER_TOK,    "5", {1,10}),
                Token(OPERATOR_TOK,   "+", {1,12}),
                Token(INTEGER_TOK,    "5", {1,14}),
                Token(SEPARATOR_TOK,  ")", {1,15}),
                Token(SEMICOLON_TOK,  ";", {1,16})}
            )
        )
    );
    Tester::tUnits.push_back(
        TestUnit(
            "testFiles/test1.kal",
            std::vector<Token>({
                Token(KEYWORD_TOK,  "int", {1,1}),
                Token(IDENTIFIER_TOK, "x", {1,5}),
                Token(OPERATOR_TOK,   "=", {1,7}),
                Token(SEPARATOR_TOK,  "(", {1,9}),
                Token(INTEGER_TOK,    "5", {1,10}),
                Token(OPERATOR_TOK,   "+", {1,12}),
                Token(INTEGER_TOK,    "5", {1,14}),
                Token(SEPARATOR_TOK,  ")", {1,15}),
                Token(SEMICOLON_TOK,  ";", {1,16}),

                Token(KEYWORD_TOK,   "int",        {2, 1}),
                Token(IDENTIFIER_TOK,   "y",       {2, 5}),
                Token(OPERATOR_TOK,   "=",         {2, 6}),
                Token(INTEGER_TOK,   "561324",     {2, 7}),
                Token(SEMICOLON_TOK,   ";",        {2, 13}),
                
                Token(IDENTIFIER_TOK,   "y",       {3, 1}),
                Token(DOUBLE_OPERATOR_TOK,   "++", {3, 2}),
                Token(SEMICOLON_TOK,   ";",        {3, 4}),
                
                Token(KEYWORD_TOK,   "double",     {4, 1}),
                Token(IDENTIFIER_TOK,   "z",       {4, 8}),
                Token(OPERATOR_TOK,   "=",         {4, 9}),
                Token(FLOAT_TOK,   "3456.3456",    {4, 10}),
                Token(SEMICOLON_TOK,   ";",        {4, 19}),
                
                
                Token(KEYWORD_TOK,  "if",          {5, 1}),
                Token(SEPARATOR_TOK,  "(",         {5, 3}),
                Token(IDENTIFIER_TOK, "x",         {5, 4}),
                Token(DOUBLE_OPERATOR_TOK,   "==", {5, 5}),
                Token(IDENTIFIER_TOK,   "y",       {5, 7}),
                Token(DOUBLE_OPERATOR_TOK,   "&&", {5, 8}),
                Token(IDENTIFIER_TOK,   "z",       {5, 10}),
                Token(DOUBLE_OPERATOR_TOK,   "!=", {5, 11}),
                Token(IDENTIFIER_TOK, "x",         {5, 13}),
                Token(SEPARATOR_TOK,  ")",         {5, 14}),
                Token(SEPARATOR_TOK,  "{",         {5, 15}),
                
                Token(SEPARATOR_TOK,  "{",         {6, 5}),

                Token(IDENTIFIER_TOK, "x",         {7, 9}),
                Token(OPERATOR_TOK,   "=",         {7, 10}),
                Token(SEPARATOR_TOK,  "(",         {7, 11}),
                Token(IDENTIFIER_TOK,   "y",       {7, 12}),
                Token(OPERATOR_TOK,   "+",         {7, 13}),
                Token(IDENTIFIER_TOK,   "z",       {7, 14}),
                Token(SEPARATOR_TOK,  ")",         {7, 15}),
                Token(SEMICOLON_TOK,   ";",        {7, 16}),
                
                Token(SEPARATOR_TOK,  "}",         {8, 5}),
                
                Token(SEPARATOR_TOK,  "}",         {9, 1}),
                Token(KEYWORD_TOK,  "else",        {9, 2}),
                Token(SEPARATOR_TOK,  "{",         {9, 6}),

                Token(KEYWORD_TOK,  "char",        {10, 5}),
                Token(IDENTIFIER_TOK, "x",         {10, 10}),
                Token(OPERATOR_TOK,   "=",         {10, 12}),
                Token(CHAR_TOK,   "\'t\'",         {10, 14}),
                Token(SEMICOLON_TOK,   ";",        {10, 17}),
                
                Token(KEYWORD_TOK,  "string",      {11, 5}),
                Token(IDENTIFIER_TOK, "s",         {11, 12}),
                Token(OPERATOR_TOK,   "=",         {11, 14}),
                Token(STRING_TOK,   "\"aoisu dhg jnv\"", {11, 16}),
                Token(SEMICOLON_TOK,   ";",        {11, 31}),

                Token(SEPARATOR_TOK,  "}",         {12, 1}),
                
                }
            )
        )
    );
    Tester::tUnits.push_back(
        TestUnit(
            "testFiles/test2.kal",
            std::vector<Token>({
                Token(KEYWORD_TOK, "int",        {1, 1}),
                Token(KEYWORD_TOK, "if",         {1, 5}),
                Token(IDENTIFIER_TOK, "identif",    {1, 8}),
                Token(KEYWORD_TOK, "char",       {1, 16}),
                Token(IDENTIFIER_TOK, "yes",        {1, 21}),
                Token(IDENTIFIER_TOK, "no",         {1, 25}),
                Token(IDENTIFIER_TOK, "maybe",      {1, 28}),
                Token(IDENTIFIER_TOK, "i",          {1, 34}),

                Token(IDENTIFIER_TOK, "dont",       {2, 1}),
                Token(IDENTIFIER_TOK, "know",       {2, 6}),
                Token(IDENTIFIER_TOK, "could",      {2, 11}),
                Token(IDENTIFIER_TOK, "you",        {2, 17}),
                Token(IDENTIFIER_TOK, "repeat",     {2, 21}),
                Token(IDENTIFIER_TOK, "the",        {2, 28}),
                
                // '\n'
                
                Token(IDENTIFIER_TOK, "question",   {8, 1}),
                Token(IDENTIFIER_TOK, "youre",      {8, 10}),
                Token(IDENTIFIER_TOK, "not",        {8, 16}),
                Token(IDENTIFIER_TOK, "the",        {8, 20}),
                Token(IDENTIFIER_TOK, "boss",       {8, 24}),
                Token(IDENTIFIER_TOK, "of",         {8, 29}),
                Token(IDENTIFIER_TOK, "me",         {8, 32}),
                Token(IDENTIFIER_TOK, "now",        {8, 35}),
                }
            )
        )
    );
}

void Tester::setup(u_int8_t inputFlags) {
    Tester::flags = inputFlags;
    Tester::setup();
}

void Tester::selectUnits(std::vector<int> units) {
    selectedIndices = units;
}

void Tester::printError(int i, int j, ErrorType errT) {

    std::cout << "\033[1;31mError\033[0m";
    std::cout << " in test unit " << i << ", token number " << j << " <" << tUnits.at(i).toks.at(j).getToken() << ">" << ":" << std::endl;

    switch (errT) {
        case TOK_TYPE:
        std::cout << "\t" << Tester::outToks.at(j).getType() << " not equal " << Tester::tUnits.at(i).toks.at(j).getType() << std::endl;
        break;

        case TOK_VAL:
        std::cout << "\t" << Tester::outToks.at(j).getToken() << " not equal " << Tester::tUnits.at(i).toks.at(j).getToken() << std::endl;
        break;

        case TOK_POS:
        std::cout << "\t" << Tester::outToks.at(j).getPos().toString() << " not equal " << Tester::tUnits.at(i).toks.at(j).getPos().toString() << std::endl;
        break;
    }
    
}

void Tester::run() {

    std::cout << "Running tests..." << std::endl;

    for (int i = 0; i < selectedIndices.size(); i++) {
        int currUnitIdx = selectedIndices.at(i);

        std::cout << "\033[1;32mTest " << currUnitIdx << ":\033[0m" << std::endl;
        
        Lexer lexer = Lexer(tUnits.at(currUnitIdx).filename);
        outToks = lexer.tokenize(tUnits.at(currUnitIdx).filename);

        if (outToks.size() != tUnits.at(currUnitIdx).toks.size()) {
            std::cout << "Number of tokens does not equal test. Test failed." << std::endl;
            break;
        }


        for (int j = 0; j < outToks.size(); j++) {
            if (tUnits.at(currUnitIdx).toks.at(j).getType() != outToks.at(j).getType()) {
                printError(currUnitIdx, j, TOK_TYPE);
                std::cout << std::endl;
                
            } else if (tUnits.at(currUnitIdx).toks.at(j).getToken() != outToks.at(j).getToken()) {
                printError(currUnitIdx, j, TOK_VAL);
                std::cout << std::endl;
                
            } else if (tUnits.at(currUnitIdx).toks.at(j).getPos() != outToks.at(j).getPos()) {
                printError(currUnitIdx, j, TOK_POS);
                std::cout << std::endl;
                
            }    
        }

        if (flags & TEST_VERBOSE) {
            std::cout << outToks.size() << " tokens (verbose):" << std::endl;
            std::cout << "Test unit " << currUnitIdx << "\t\t\t\t\t" << tUnits.at(currUnitIdx).filename << " tokenized" << std::endl;
            for (int j = 0; j < outToks.size(); j++) {
                std::cout << tUnits.at(currUnitIdx).toks.at(j).toString() << "\t\t\t" << outToks.at(j).toString() << std::endl;
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Tests done." << std::endl;
}