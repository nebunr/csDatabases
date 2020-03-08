//SQL Command Handler Header
//By: Benjamin Estela

//Precompiler Directives
#ifndef COMMANDS_H
#define COMMANDS_H

//Header Files
#include "database_headers.h"
#include "cmdstates.h"

//Class Prototypes
//Commands class holds the important variables needed to execute the .sql commands
class Commands{
    public:
        //Constructors
        Commands();
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
        void SelectTable(); //DONE*
        void InsertIntoTable(); //DONE*
        void UpdateTable(); //DONE*
        void SetTable(); //DONE*
        void FromTable(); //DONE*
        void WhereTable(); //life is pain
        void DeleteFromTable(); //DONE*
        //Set Methods
        void SetCommand(int command);
        void SetManipulation(int manipulation);
        void SetLine(std::string line);
        void SetFile(std::string file);
        void SetPrevSQL(std::string prevsql);
        //Get Methods
        int GetCommand();
        int GetManipulation();
        std::string GetLine();
        std::string GetFile();
        std::string GetPrevSQL();
    private:
        int m_command;
        int m_manipulation;
        std::string m_line;
        std::string m_file;
        std::string m_prevsql;
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