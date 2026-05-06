#ifndef FILE_POSITION_H
#define FILE_POSITION_H
#include <vector>
#include <string>
#include <sstream>

class FilePosition {
    private:
    unsigned int line;
    unsigned int col;

    public:
    FilePosition();
    FilePosition(unsigned int l, unsigned int c);
    unsigned int getLine();
    unsigned int getCol();
    std::vector<unsigned int> getAbsolute();
    void setLine(unsigned int l);
    void setCol(unsigned int pos);
    unsigned int operator++(int);
    void newLine();
    std::string toString();
    bool operator==(FilePosition rhs);
    bool operator!=(FilePosition rhs);
};
#endif