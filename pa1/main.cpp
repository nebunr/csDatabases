//main.cpp
//By: Benjamin Estela

//Header Files
#include "parser.h"
using namespace std;

//Main Function
int main(int argc, char** argv)
{
    try
    {
        if(!argv[1])
        {
            throw "No filename found.";
        }
    }
    catch(const char* error)
    {
        std::cerr << error << '\n';
    }
    
    ifstream sqlFile;
    sqlFile.open(argv[1]);
    if(sqlFile.is_open())
    {
        ReadFile(sqlFile);
    }
    sqlFile.close();
    
    return 0;
}