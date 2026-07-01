#include "FilePosition.hpp"

FilePosition::FilePosition() {
    line = 1;
    col = 1;
}
FilePosition::FilePosition(unsigned int l, unsigned int c) {
    line = l;
    col = c;
}
std::vector<unsigned int> FilePosition::getAbsolute() {
    return std::vector<unsigned int>(line, col);
}
unsigned int FilePosition::getLine(){
    return line;
}
unsigned int FilePosition::getCol(){
    return col;
}
void FilePosition::setLine(unsigned int l) {
    line = l;
}
void FilePosition::setCol(unsigned int pos) {
    col = pos;
}
unsigned int FilePosition::operator++(int) {
    col++;
    return this->col;
}
void FilePosition::newLine() {
    col = 0;
    line++;
}
std::string FilePosition::toString() {
    std::stringstream ss;
    ss << "[" << line << ", " << col << "]";
    return ss.str();
}
bool FilePosition::operator==(FilePosition rhs) {
    if (this->line != rhs.line ||
        this->col != rhs.col
    ) return false;
    return true;
}
bool FilePosition::operator!=(FilePosition rhs) {
    if (this->line != rhs.line ||
        this->col != rhs.col
    ) return true;
    return false;
}
void FilePosition::operator+=(unsigned int rhs) {
    this->col += rhs;
}