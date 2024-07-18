#include <iostream>
#include <string>

using namespace std;

/*

A program with the goal of copying the Project Template into a new named directory in projects
just to make it more like an actual engine. 

*/

int main(int count, char** args)
{
    if (count < 2)
    {
        return -1;
    }

    system("cd projects");

    string mkdir = "mkdir ";
    mkdir.append(args[1]);
    system(mkdir.c_str());

    return 0;
}