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
    t.selectUnits({TEST0, TEST1, TEST2, TEST3, TEST4});
    t.run();
    
    return 0;
}