#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

#include "Tester.hpp"


#define TEST0 0
#define TEST1 1

int main(int argc, char **argv) {
    
    Tester t;
    t.setup(TEST_VERBOSE);
    t.setSelectedUnits({TEST0, TEST1});
    t.run();
    
    return 0;
}