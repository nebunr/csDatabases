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
    m_manipulation = NONE_DATA;
    m_line = "";
    m_file = "";
    m_prevsql = "";
}

//Destructor (not fully implemented)
Commands::~Commands(){}

//CREATE DATABASE
void Commands::CreateDatabase()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ';'); //tempStr is now the variable
    int len = tempStr.length();
    char fileName[len + 1];
    strcpy(fileName, tempStr.c_str());
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
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ';'); //tempStr is now the variable
    int len = tempStr.length();
    char fileName[len + 1];
    strcpy(fileName, tempStr.c_str());
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
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ';'); //tempStr is now the variable
    int len = tempStr.length();
    char folderName[len + 1];
    strcpy(folderName, tempStr.c_str());
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
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' '); //tempStr is now the variable
    if(access(tempStr.c_str(), F_OK) != -1)
    {
        cerr << "!Failed to create table " << tempStr.c_str() << " because it already exists." << endl;
    }
    else
    {
        ofstream file;
        file.open(tempStr.c_str());
        cout << "Table " << tempStr.c_str() << " created." << endl;
        //Splits up parameters.
        getline(ss, tempStr, '(');
        getline(ss, tempStr, ';');
        string strWrite;
        strWrite = tempStr.substr(0, tempStr.size() - 1);
        //replace ", " with " | "
        size_t startPos = 0;
        string from = ", ";
        string to = " | "; //may need to fix?
        while((startPos = strWrite.find(from, startPos)) != string::npos)
        {
            strWrite.replace(startPos, from.length(), to);
            startPos += to.length();
        }
        file << strWrite << endl;
        file.close();
        
    }
    
    return;
}

//DROP TABLE
void Commands::DropTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ';'); //tempStr is now the variable
    //remove deletes a file
    if(remove(tempStr.c_str()) != 0)
    {
        cerr << "!Failed to delete table " << tempStr.c_str() << " because it does not exist." << endl;
    }
    else
    {
        cout << "Table " << tempStr.c_str() << " deleted." << endl;
    }

    return;
}

//ALTER TABLE
void Commands::AlterTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' '); //tempStr is now the variable
    int len = tempStr.length();
    char tableName[len + 1];
    strcpy(tableName, tempStr.c_str());

    string toupperStr = m_line;
    transform(toupperStr.begin(), toupperStr.end(), toupperStr.begin(), ::toupper);

    //Can add more ALTER COMMANDS in the future
    //ADD is basically concat to the end of the table
    if(toupperStr.find("ADD") != string::npos)
    {
        getline(ss, tempStr, ' ');
        getline(ss, tempStr, ';');
        ofstream file;
        file.open(tableName, ios_base::app);
        if(tempStr.size() >= 1)
        {
            file << " | " << tempStr; //TODO: better parsing for more vars
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

//SELECT * FROM (Query All)
void Commands::SelectFromTable()
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
            SetFile(tableName);
            while(getline(file, tempStr))
            {
                if(tempStr.size() > 2) //test more
                {
                    cout << tempStr << endl;
                }
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

//SELECT (Query Specific)
void Commands::SelectTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, '\n');
    if(!tempStr.empty())
    {
        tempStr.pop_back();
        if(tempStr.back() == ' ')
        {
            tempStr.pop_back();
        }
    }
    //cout << "Query:" << tempStr << "+" << endl;
    SetPrevSQL(tempStr);
    SetManipulation(SELECT_DATA);
    return;
}

//INSERT INTO
void Commands::InsertIntoTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' '); //tempStr is now the variable
    int len = tempStr.length();
    char tableName[len + 1];
    strcpy(tableName, tempStr.c_str());

    string toupperStr = m_line;
    transform(toupperStr.begin(), toupperStr.end(), toupperStr.begin(), ::toupper);

    if(toupperStr.find("VALUES") != string::npos)
    {
        getline(ss, tempStr, '(');
        getline(ss, tempStr, ')');
        //parse values
        //removes whitespace
        tempStr.erase(remove_if(tempStr.begin(), tempStr.end(), isSpace()), tempStr.end());
        string strWrite;
        strWrite = tempStr.substr(0, tempStr.size());
        //replace "," with " | "
        size_t startPos = 0;
        string from = ",";
        string to = " | "; //may need to fix?
        while((startPos = strWrite.find(from, startPos)) != string::npos)
        {
            strWrite.replace(startPos, from.length(), to);
            startPos += to.length();
        }
        //open file
        ofstream file;
        file.open(tableName, ios_base::app);
        if(tempStr.size() >= 1)
        {
            file << strWrite << endl;
        }
        
        file.close();

        //can only handle 1 record at a time
        cout << "1 new record inserted." << endl;
    }
    else
    {
        cerr << "!Failed to insert into table" << tableName << "due to invalid command." << endl;
    }
    return;
}

//UPDATE
void Commands::UpdateTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, '\n'); //???
    tempStr.erase(remove_if(tempStr.begin(), tempStr.end(), isSpace()), tempStr.end());
    ifstream file;
    file.open(tempStr);
    if(file.is_open())
    {
        SetFile(tempStr);
        SetManipulation(UPDATE_DATA);
        //cout << "Table to update: " << tempStr << endl;
    }
    else
    {
        cerr << "!Failed to find table " << tempStr << " because it does not exist." << endl;
    }
    file.close();
    return;
}

//SET
void Commands::SetTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, '\n');
    if(!tempStr.empty())
    {
        tempStr.pop_back();
        if(tempStr.back() == ' ')
        {
            tempStr.pop_back();
        }
    }
    SetPrevSQL(tempStr);
    //cout << "set: " << tempStr << "+" << endl;
    return;
}

//FROM
void Commands::FromTable()
{
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, '\n'); //???
    tempStr.erase(remove_if(tempStr.begin(), tempStr.end(), isSpace()), tempStr.end());
    ifstream file;
    file.open(tempStr);
    if(file.is_open())
    {
        SetFile(tempStr);
        SetManipulation(UPDATE_DATA);
        //cout << "Table to query: " << tempStr << endl;
    }
    else
    {
        cerr << "!Failed to find table " << tempStr << " because it does not exist." << endl;
    }
    file.close();
    return;
}

//WHERE
void Commands::WhereTable()
{
    if(GetManipulation() == UPDATE_DATA)
    {
        cout << "UPDATE WHERE?" << endl;
    }
    else if(GetManipulation() == DELETE_DATA)
    {
        cout << "DELETE WHERE?" << endl;
    }
    else if(GetManipulation() == SELECT_DATA)
    {
        cout << "SELECT WHERE?" << endl;
    }
    else
    {
        cerr << "!Failed to manipulate data as improper function was read in." << endl;
    }

    //With data manipulation complete, the table name does not need to be stored anymore.
    SetManipulation(NONE_DATA);
    SetFile("");
    SetPrevSQL("");
    return;
}

//DELETE FROM
void Commands::DeleteFromTable()
{
    //cout << "DELETE" << endl;
    string tempStr;
    stringstream ss(m_line);
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, ' ');
    getline(ss, tempStr, '\n');
    tempStr.erase(remove_if(tempStr.begin(), tempStr.end(), isSpace()), tempStr.end());
    ifstream file;
    file.open(tempStr);
    if(file.is_open())
    {
        SetFile(tempStr);
        SetManipulation(DELETE_DATA);
        //cout << "Table to delete: " << tempStr << endl;
    }
    else
    {
        cerr << "!Failed to find table " << tempStr << " because it does not exist." << endl;
    }
    file.close();
    return;
}

//Set Methods
void Commands::SetCommand(int command)
{
    m_command = command;
}

void Commands::SetManipulation(int manipulation)
{
    m_manipulation = manipulation;
}

void Commands::SetLine(string line)
{
    m_line = line;
}

void Commands::SetFile(string file)
{
    m_file = file;
}

void Commands::SetPrevSQL(string prevsql)
{
    m_prevsql = prevsql;
}

//Get Methods
int Commands::GetCommand()
{
    return m_command;
}

int Commands::GetManipulation()
{
    return m_manipulation;
}

string Commands::GetLine()
{
    return m_line;
}

string Commands::GetFile()
{
    return m_file;
}

string Commands::GetPrevSQL()
{
    return m_prevsql;
}