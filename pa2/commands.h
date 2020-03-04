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
        Commands(int command, std::string line);
        ~Commands();
        //Databases
        void CreateDatabase();
        void DropDatabase();
        //Tables (pa1)
        void Use();
        void CreateTable();
        void DropTable();
        void AlterTable();
        void QueryTable();
        //Tables (pa2)
        void InsertIntoTable();
        void UpdateTable();
        void SetTable();
        void FromTable();
        void WhereTable();
        void DeleteFromTable();
        //Set Methods
        void SetCommand(int command);
        void SetLine(std::string m_line);
        //Get Methods
        int GetCommand();
        std::string GetLine();
    private:
        int m_command;
        std::string m_line;
};

//Terminating Precompiler Directives
#endif //COMMANDS_H