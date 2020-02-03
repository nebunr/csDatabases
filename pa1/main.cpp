//make; ./pa1 PA1_test.sql
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char** argv)
{
    try
    {
        if(!argv[1])
        {
            throw "No filename found.";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    ifstream sqlFile;
    sqlFile.open(argv[1]);
    
    cout << "testing: " << argv[1] << endl;
    
    sqlFile.close();
    
    return 0;
}