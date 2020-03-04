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
    //cmd and strInput are set for the command class
    string strInput;
    string strTemp;
    int cmd = -1;
    bool flag = false;
    Commands command;
    while(!file.eof() || !flag)
    {
        getline(file, strInput, '\n');
        strTemp = strInput;
        transform(strTemp.begin(), strTemp.end(), strTemp.begin(), ::toupper);
        //For end of .sql file
        if(strTemp.find(".EXIT") != string::npos)
        {
            //End reading file
            cout << "All done." << endl;
            flag = true;
            break;
        }
        //For comments
        else if ((strTemp.find("--") != string::npos))
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
            cmd = ParseCommand(strTemp);
            //Send command to commands function(s)
            if(cmd != -1)
            {
                command.SetCommand(cmd);
                command.SetLine(strInput);
                //For future commands: 
                //update this and the below function, 
                //and create relevant command function
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
                        command.AlterTable();
                        break;
                    case SELECT_FROM:
                        command.QueryTable();
                        break;
                    case INSERT_INTO:
                        command.InsertIntoTable();
                        break;
                    case UPDATE:
                        command.UpdateTable();
                        break;
                    case SET:
                        command.SetTable();
                        break;
                    case FROM:
                        command.FromTable();
                        break;
                    case WHERE:
                        command.WhereTable();
                        break;
                    case DELETE_FROM:
                        command.DeleteFromTable();
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return;
}

//Looks for SQL command to return
//Uses enum from cmdstates.h
int ParseCommand(string &str)
{
    if(str.find("CREATE DATABASE ") != string::npos)
    {
        return CREATE_DB;
    }
    else if(str.find("DROP DATABASE ") != string::npos)
    {
        return DROP_DB;
    }
    else if(str.find("USE ") != string::npos)
    {
        return USE;
    }
    else if(str.find("CREATE TABLE ") != string::npos)
    {
        return CREATE_TABLE;
    }
    else if(str.find("DROP TABLE ") != string::npos)
    {
        return DROP_TABLE;
    }
    else if(str.find("ALTER TABLE ") != string::npos)
    {
        return ALTER_TABLE;
    }
    else if((str.find("SELECT ") != string::npos) && (str.find(" FROM") !=string::npos))
    {
        return SELECT_FROM;
    }
    else if((str.find("INSERT ") != string::npos) && (str.find(" INTO") !=string::npos))
    {
        return INSERT_INTO;
    }
    else if(str.find("UPDATE ") != string::npos)
    {
        return UPDATE;
    }
    else if(str.find("SET ") != string::npos)
    {
        return SET;
    }
    else if(str.find("FROM ") != string::npos)
    {
        return FROM;
    }
    else if(str.find("WHERE ") != string::npos)
    {
        return WHERE;
    }
    else if((str.find("DELETE ") != string::npos) && (str.find(" FROM") !=string::npos))
    {
        return DELETE_FROM;
    }
    else
    {
        cout << "Invalid command found." << endl;
        return -1;
    }
}