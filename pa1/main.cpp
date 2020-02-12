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
    //make; ./pa PA1_test.sql
    cout << "testing: " << argv[1] << endl;
    TestFunc();
    
    sqlFile.close();
    
    return 0;
}
//End of Program