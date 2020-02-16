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
#include <unistd.h>

//Class Prototypes
class Commands{
    public:
        Commands();
        Commands(int command, std::string line);
        void CreateDatabase();
        void DropDatabase();
        void Use();
    private:
        int m_command;
        std::string m_line;
};

#endif //COMMANDS_H