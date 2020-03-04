//SQL Command Handler Header
//By: Benjamin Estela

//Precompiler Directives
#ifndef COMMANDS_H
#define COMMANDS_H

//Header Files
#include "database_headers.h"

//Class Prototypes
//Commands class holds the important variables needed to execute the .sql commands
class Commands{
    public:
        //Constructors
        Commands();
        Commands(int command, std::string line, std::string file);
        ~Commands();
        //Databases
        void CreateDatabase();
        void DropDatabase();
        //Tables (pa1)
        void Use();
        void CreateTable();
        void DropTable();
        void AlterTable();
        void SelectFromTable();
        //Tables (pa2)
        void SelectTable();
        void InsertIntoTable(); //DONE
        void UpdateTable(); //DONE
        void SetTable();
        void FromTable();
        void WhereTable();
        void DeleteFromTable();
        //Set Methods
        void SetCommand(int command);
        void SetLine(std::string m_line);
        void SetFile(std::string m_file);
        //Get Methods
        int GetCommand();
        std::string GetLine();
        std::string GetFile();
    private:
        int m_command;
        std::string m_line;
        std::string m_file;
};

//Struct with boolean operator that returns 
//true if char is a whitespace
struct isSpace
{
    bool operator()(unsigned c)
    {
        return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f');
    }
};

//Terminating Precompiler Directives
#endif //COMMANDS_H