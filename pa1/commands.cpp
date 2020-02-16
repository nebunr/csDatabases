//SQL Command Handler
//By: Benjamin Estela

//Header Files
#include "commands.h"
#include "cmdstates.h"
using namespace std;

//Class Function Implementation
//Default Constructor
Commands::Commands()
{
    m_command = -1;
    m_line = "";
}

//Parameterized Constructor
Commands::Commands(int command, string line)
{
    m_command = command;
    m_line = line;
}

//Complete Destructor
Commands::~Commands(){}

//CREATE DATABASE
void Commands::CreateDatabase()
{
    string tempVar;
    stringstream ss(m_line);
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ';'); //temp is now the variable
    int len = tempVar.length();
    char fileName[len + 1];
    strcpy(fileName, tempVar.c_str());
    if(mkdir(fileName, 0777) == -1)
    {
        cerr << "!Failed to create database " << fileName << " because it already exists." << endl;
    }
    else
    {
        cout << "Database " << fileName << " created." << endl;
    }
    
}

//DROP DATABASE
void Commands::DropDatabase()
{
    string tempVar;
    stringstream ss(m_line);
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ';'); //temp is now the variable
    int len = tempVar.length();
    char fileName[len + 1];
    strcpy(fileName, tempVar.c_str());
    if(rmdir(fileName) == -1)
    {
        cerr << "!Failed to delete " << fileName << " because it does not exist." << endl;
    }
    else
    {
        cout << "Database " << fileName << " deleted." << endl;
    }
}

//USE
void Commands::Use()
{
    string tempVar;
    stringstream ss(m_line);
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ';'); //temp is now the variable
    int len = tempVar.length();
    char folderName[len + 1];
    strcpy(folderName, tempVar.c_str());
    if(chdir(folderName) == -1)
    {
        //error handling that chdir's one folder back
        char prevDir[len + 4];
        strcpy(prevDir, "../");
        strcat(prevDir, folderName);
        if(chdir(prevDir) == -1)
        {
            cerr << "!Failed to access " << folderName << "." << endl;
        }
        else
        {
            cout << "Using database " << folderName << "." << endl;
        }
    }
    else
    {
        cout << "Using database " << folderName << "." << endl;
    }
    return;
}

//CREATE TABLE
void Commands::CreateTable()
{
    return;
}

//DROP TABLE
void Commands::DropTable()
{
    return;
}

//ALTER TABLE (Update)
void Commands::UpdateTable()
{
    return;
}

//SELECT * TABLE (Query)
void Commands::QueryTable()
{
    //* = all?
    return;
}

//Set Methods
void Commands::SetCommand(int command)
{
    m_command = command;
}

void Commands::SetLine(string line)
{
    m_line = line;
}

//Get Methods
int Commands::GetCommand()
{
    return m_command;
}

string Commands::GetLine()
{
    return m_line;
}