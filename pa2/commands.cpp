//SQL Command Handler
//By: Benjamin Estela

//Header Files
#include "commands.h"
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

//Destructor (not fully implemented)
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
    //rmdir removes folder
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
    //chdir is basically cd in bash
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
        //Splits up parameters.
        getline(ss, tempVar, '(');
        getline(ss, tempVar, ';');
        string strWrite;
        strWrite = tempVar.substr(0, tempVar.size() - 1);
        //replace ", " with " | "
        size_t startPos = 0;
        string from = ", ";
        string to = " | "; //may need to fix?
        while((startPos = strWrite.find(from, startPos)) != string::npos)
        {
            strWrite.replace(startPos, from.length(), to);
            startPos += to.length();
        }
        file << strWrite;
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
    //remove deletes a file
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

//ALTER TABLE
void Commands::AlterTable()
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

    //Can add more ALTER COMMANDS in the future
    //ADD is basically concat to the end of the table
    if(tempStr.find("ADD") != string::npos)
    {
        getline(ss, tempVar, ' ');
        getline(ss, tempVar, ';');
        ofstream file;
        file.open(tableName, ios_base::app);
        if(tempVar.size() >= 1)
        {
            file << " | " << tempVar; //TODO: better parsing for more vars
        }
        
        file.close();
        cout << "Table " << tableName << " modified." << endl;
    }
    else
    {
        cerr << "!Failed to alter table" << tableName << "due to invalid command." << endl;
    }
    
    return;
}

//SELECT * FROM (Query)
void Commands::QueryTable()
{
    string tempStr;
    string tableName;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tableName, ';');
    //This function basically prints out everything in the file
    //* is used for all and can with more if statements, can be used for different queries
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

//INSERT INTO
void Commands::InsertIntoTable()
{
    return;
}

//UPDATE
void Commands::UpdateTable()
{
    return;
}

//SET
void Commands::SetTable()
{
    return;
}

//FROM
void Commands::FromTable()
{
    return;
}

//WHERE
void Commands::WhereTable()
{
    return;
}

//DELETE FROM
void Commands::DeleteFromTable()
{
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