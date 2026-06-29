#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

#include "Tester.hpp"

int main(int argc, char **argv) {
    
    Tester t;
    t.setup(TEST_VERBOSE);
    t.selectUnits({TEST3});
    t.run();
    
    return 0;
}