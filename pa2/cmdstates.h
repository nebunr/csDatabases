//Header File for Command States
//By: Benjamin Estela

//Precompiler Directives
#ifndef CMDSTATES_H
#define CMDSTATES_H

//Enumeration Declaration
//For .sql commands
enum {
    CREATE_DB,
    DROP_DB,
    USE,
    CREATE_TABLE,
    DROP_TABLE,
    ALTER_TABLE,
    SELECT_FROM,
    SELECT,
    INSERT_INTO,
    UPDATE,
    SET,
    FROM,
    WHERE,
    DELETE_FROM,
};
//For data manipulation
enum {
    NONE_DATA,
    UPDATE_DATA,
    DELETE_DATA,
    SELECT_DATA,
};

//Terminating Precompiler Directives
#endif //CMDSTATES_H