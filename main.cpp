#include <string>
#include <regex>

const int SIZE = 10;
int data[SIZE];

extern "C" {
void add(int value) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = data[i] + value;
    }
}
}

extern "C" {
int *getData() {
    return &data[0];
}
}

extern "C" {
    void set() {
        for (int i = 0; i < SIZE; i++) {
            data[i] = int("a");
        }
    }
}

#include "emscripten.h"
extern "C" {
int * EMSCRIPTEN_KEEPALIVE concat(int* a, int* b, int asize, int bsize)
{
    int bufSize = asize + bsize;
    int result[bufSize];
    for (int i = 0; i < asize; i++) {
        result[i] = a[i];
    }

    for (int i = 0; i < bsize; i++) {
        result[asize + i] = b[i];
    }

    auto arrayPtr = &result[0];
    return arrayPtr;
}
}

std::string charToString(char* a, int size) {
    std::string s(a);
    return s;
}

extern "C" {
int  EMSCRIPTEN_KEEPALIVE contains(int* a, int* b, int asize, int bsize)
{
    char input[asize+1];
    for (int i = 0; i < asize; i++) {
        input[i] = a[i];
    }
    input[asize] = 0;

//    std::string s("hi");
//    std::string in_str = charToString(input, asize + 1);

//    std::regex word_regex("(\\S+)");
//
//    auto w_begin = std::sregex_iterator (in_str.begin(), in_str.end(), word_regex);
//    auto w_end = std::sregex_iterator();
//
//    return std::distance(w_begin, w_end);


    char match = b[0];

    for (int i = 0; i < asize; i++) {
        if (input[i] == match)
            return i;
    }

    return 0;
}
}