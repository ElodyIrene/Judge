#ifndef OUTPUT_H
#define OUTPUT_H
#include "std.h"

class OUTPUT
{
public:
    void Output(const char fatherPath[]);
    void Capture_o(string path, vector<string>& files);
    bool Compare(const char file1[], const char file2[]);
    void Store(const char fatherPath[], char file1[], char file2[], bool res, const char equal[], const char inequal[]);
};

#endif
