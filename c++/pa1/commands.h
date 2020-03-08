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
        Commands();
        Commands(int command, std::string line);
        ~Commands();

        void CreateDatabase();
        void DropDatabase();
        void Use();
        void CreateTable();
        void DropTable();
        void UpdateTable();
        void QueryTable();

        void SetCommand(int command);
        void SetLine(std::string m_line);

        int GetCommand();
        std::string GetLine();

    private:
        int m_command;
        std::string m_line;
};

//Terminating Precompiler Directives
#endif //COMMANDS_H