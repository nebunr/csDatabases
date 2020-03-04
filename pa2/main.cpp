//Main C++ File
//Begins program and sets up file io
//By: Benjamin Estela

//Header Files
#include "parser.h"
using namespace std;

//Main Function
int main(int argc, char** argv)
{
    //This is a filename-argument only program
    //Error handling needed incase given file is not found
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

    //Open file and read to execute database commands
    ifstream sqlFile;
    sqlFile.open(argv[1]);
    if(sqlFile.is_open())
    {
        ReadFile(sqlFile);
    }

    //Close file and end program right after
    sqlFile.close();

    return 0;
}