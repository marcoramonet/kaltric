#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

void print(std::string msg) {
    std::cout << msg << std::endl;
}

void printBinary(u_int8_t num) {
    for (int i = sizeof(u_int8_t) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

#endif