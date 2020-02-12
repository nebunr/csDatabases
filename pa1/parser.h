//String Parser Header
//By: Benjamin Estela

//Precompiler Directives
#ifndef PARSER_H
#define PARSER_H

#include <iostream> //for basic io
#include <fstream> //for file io
#include <algorithm> //for toupper
#include <string> //for strings

//Function Prototypes
void ReadFile(std::ifstream &file);
void ParseCommand();

//Terminating Precompiler Directives
#endif //PARSER_H