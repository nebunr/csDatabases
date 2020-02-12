//String Parser
//By: Benjamin Estela

//Header Files
#include "parser.h"
using namespace std;

//Function Implementation
void ReadFile(ifstream &file)
{
    int i = 0;
    string strInput;
    while(!file.eof())
    {
        i++;
        getline(file, strInput, '\n');
        transform(strInput.begin(), strInput.end(), strInput.begin(), ::toupper);
        //For end of .sql file
        if(strInput.find(".EXIT") != string::npos)
        {
            //End reading file
            cout << "All done." << endl;
            break;
        }
        //For comments
        else if ((strInput.find("--") != string::npos) || (strInput.find(";") == string::npos))
        {
            //Do nothing
            //NOTE: 
            //  Due to this conditional, every non-commented functional line needs a ";". 
            //  May need to fix in the future
        }
        //For all main functionality
        else
        {
            //String parsing
            //cout << strInput << endl;
        }
    }
    //cout << i;
    return;
}
void ParseCommand()
{
    return;
}