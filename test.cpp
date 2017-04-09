#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
    string str;
    char s[40];

    sprintf(s, "%d", argc);

    str = s;

    cout << str << endl;
    
    return 0;
}
