#ifndef EXECUTE_H
#define EXECUTE_H
#include "std.h"

class EXECUTE
{
public:
    void Execute(const char fatherPath[]);
    void Capture_e(string path, vector<string>& files);
    void Get_name(string fatherPath, string file, string* name);
    void Write_sh(string path, string name);
    void Compile(string path, string name);
};

#endif
