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
    string temp;
    while(!file.eof())
    {
        i++;
        getline(file, strInput, '\n');
        temp = strInput;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        //For end of .sql file
        if(temp.find(".EXIT") != string::npos)
        {
            //End reading file
            cout << "All done." << endl;
            break;
        }
        //For comments
        else if ((temp.find("--") != string::npos) || (temp.find(";") == string::npos))
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
            ParseCommand(strInput);
            //send command to commands function(s)
        }
    }
    //cout << i;
    return;
}
void ParseCommand(string str)
{
    //for toupper, just set the commands toupper and leave the vars, etc. as normal
    //transform(strInput.begin(), strInput.end(), strInput.begin(), ::toupper);
    //cout << str << endl;
    return;
}