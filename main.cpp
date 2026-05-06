#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

#include "Tester.hpp"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define TEST0 0

int main(int argc, char **argv) {
    
    Tester t;
    t.setup(TEST_VERBOSE);
    t.setSelectedUnits({TEST0});
    t.run();
    
    return 0;
}