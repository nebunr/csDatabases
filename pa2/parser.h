//String Parser Header
//By: Benjamin Estela

//Precompiler Directives
#ifndef PARSER_H
#define PARSER_H

//Header Files
#include "database_headers.h"

//Function Prototypes
void ReadFile(std::ifstream &file);
int ParseCommand(std::string &str);

//Terminating Precompiler Directives
#endif //PARSER_H