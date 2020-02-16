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
    string tempVar;
    stringstream ss(m_line);
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' '); //temp is now the variable
    if(access(tempVar.c_str(), F_OK) != -1)
    {
        cerr << "!Failed to create table " << tempVar.c_str() << " because it already exists." << endl;
    }
    else
    {
        ofstream file;
        file.open(tempVar.c_str());
        cout << "Table " << tempVar.c_str() << " created." << endl;
        getline(ss, tempVar, ';');
        //TODO: Split up parameters.
        file << tempVar;
        file.close();
        
    }
    
    return;
}

//DROP TABLE
void Commands::DropTable()
{
    string tempVar;
    stringstream ss(m_line);
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ';'); //temp is now the variable
    if(remove(tempVar.c_str()) != 0)
    {
        cerr << "!Failed to delete table " << tempVar.c_str() << " because it does not exist." << endl;
    }
    else
    {
        cout << "Table " << tempVar.c_str() << " deleted." << endl;
    }

    return;
}

//ALTER TABLE (Update)
void Commands::UpdateTable()
{
    string tempVar;
    stringstream ss(m_line);
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' ');
    getline(ss, tempVar, ' '); //temp is now the variable
    int len = tempVar.length();
    char tableName[len + 1];
    strcpy(tableName, tempVar.c_str());

    string tempStr = m_line;
    transform(tempStr.begin(), tempStr.end(), tempStr.begin(), ::toupper);

    if(tempStr.find("ADD") != string::npos)
    {
        getline(ss, tempVar, ' ');
        getline(ss, tempVar, ';');
        ofstream file;
        file.open(tableName, ios_base::app);
        file << tempVar; //TODO: verify w/spaces and better parsing
        file.close();
        cout << "Table " << tableName << " modified." << endl;
    }
    else
    {
        cerr << "!Failed to alter table" << tableName << "due to invalid command." << endl;
    }
    
    return;
}

//SELECT * TABLE (Query)
void Commands::QueryTable()
{
    string tempStr;
    string tableName;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tableName, ';');
    if(m_line.find(" * ") != string::npos)
    {
        ifstream file;
        file.open(tableName);
        if(file.is_open())
        {
            while(getline(file, tempStr))
            {
                cout << tempStr << endl;
            }
        }
        else
        {
            cerr << "!Failed to query table " << tableName << " because it does not exist." << endl;
        }
        file.close();
    }

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