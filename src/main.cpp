#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Tester.hpp"

int main(int argc, char **argv) {
    
    Tester t;
    t.setup(TEST_VERBOSE);
    t.run();
    
    return 0;
}