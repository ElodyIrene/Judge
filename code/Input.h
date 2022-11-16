#ifndef INPUT_H
#define INPUT_H
#include "std.h"

class INPUT
{
public:
    void Input(const char fatherPath[]);
    void Capture_i(string path, vector<string>& files);
    void Deal_format(const char file[], const char in[]);
    void Generate_input(const char in[], int s, char Format[], int A, int B);
};

#endif
