//SQL Command Handler Header
//By: Benjamin Estela

//Precompiler Directives
#ifndef COMMANDS_H
#define COMMANDS_H

//Header Files
#include <iostream> //for basic io
#include <fstream> //for file io
#include <string> //for strings
#include <bits/stdc++.h> //for stringstream
#include <sys/stat.h> //for mkdir
#include <unistd.h> //for rmdir

//Class Prototypes
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

#endif //COMMANDS_H