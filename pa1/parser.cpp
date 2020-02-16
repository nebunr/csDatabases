//String Parser
//By: Benjamin Estela

//Header Files
#include "parser.h"
#include "cmdstates.h"
#include "commands.h"
using namespace std;

//Function Implementation
void ReadFile(ifstream &file)
{
    int i = 0;
    string strInput;
    string temp;
    int command = -1;
    bool flag = false;
    while(!file.eof() || !flag)
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
            flag = true;
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
            command = ParseCommand(strInput, temp);
            //Send command to commands function(s)
            if(command != -1)
            {
                //
            }
            
        }
    }
    //cout << i;
    return;
}
int ParseCommand(string &str, string &temp)
{
    if(temp.find("CREATE DATABASE ") != string::npos)
    {
        cout << "createDB" << endl;
        return CREATE_DB;
    }
    else if(temp.find("DROP DATABASE ") != string::npos)
    {
        cout << "dropDB\n";
        return DROP_DB;
    }
    else if(temp.find("USE ") != string::npos)
    {
        cout << "use\n";
        return USE;
    }
    else if(temp.find("CREATE TABLE ") != string::npos)
    {
        cout << "createTABLE\n";
        return CREATE_TABLE;
    }
    else if(temp.find("DROP TABLE ") != string::npos)
    {
        cout << "dropTABLE\n";
        return DROP_TABLE;
    }
    else if(temp.find("ALTER TABLE ") != string::npos)
    {
        cout << "alterTABLE\n";
        return ALTER_TABLE;
    }
    else if((temp.find("SELECT ") != string::npos) && (temp.find(" FROM") !=string::npos))
    {
        cout << "selectFROM\n";
        return SELECT_FROM;
    }
    else
    {
        cout << "Invalid command found." << endl;
        return -1;
    }
}