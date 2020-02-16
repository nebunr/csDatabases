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
    int i = 0; //for counting lines, maybe delete
    string strInput;
    string temp;
    int cmd = -1;
    bool flag = false;
    Commands command;
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
            cmd = ParseCommand(strInput, temp);
            //Send command to commands function(s)
            if(cmd != -1)
            {
                command.SetCommand(cmd);
                command.SetLine(strInput);
                switch(cmd)
                {
                    case CREATE_DB:
                        command.CreateDatabase();
                        break;
                    case DROP_DB:
                        command.DropDatabase();
                        break;
                    case USE:
                        command.Use();
                        break;
                    case CREATE_TABLE:
                        command.CreateTable();
                        break;
                    case DROP_TABLE:
                        command.DropTable();
                        break;
                    case ALTER_TABLE:
                        command.UpdateTable();
                        break;
                    case SELECT_FROM:
                        command.QueryTable();
                        break;
                    default:
                        break;
                }
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
        return CREATE_DB;
    }
    else if(temp.find("DROP DATABASE ") != string::npos)
    {
        return DROP_DB;
    }
    else if(temp.find("USE ") != string::npos)
    {
        return USE;
    }
    else if(temp.find("CREATE TABLE ") != string::npos)
    {
        return CREATE_TABLE;
    }
    else if(temp.find("DROP TABLE ") != string::npos)
    {
        return DROP_TABLE;
    }
    else if(temp.find("ALTER TABLE ") != string::npos)
    {
        return ALTER_TABLE;
    }
    else if((temp.find("SELECT ") != string::npos) && (temp.find(" FROM") !=string::npos))
    {
        return SELECT_FROM;
    }
    else
    {
        cout << "Invalid command found." << endl;
        return -1;
    }
}