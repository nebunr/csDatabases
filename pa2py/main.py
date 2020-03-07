#!/usr/bin/env python3

"""
File: Main Python3 File
By: Benjamin Estela
Class: CS 457
Notes:
    Assuming it is ran like below:
    $ python3 main.py PA#_test.sql
    then len(sys.argv) is 2 and sys.argv[1] is PA#_test.sql
"""

#Header Files
import commands
#Packages
import sys

#Free Function Definitions
#Read in each line and call commands
def ReadLine(line, cmd):
    #Exit Function
    if(line.upper().find(".EXIT", 0, 5) != -1):
        exit("All Done.")
    #Comments and Empty Lines
    elif((line.find("--", 0, 2) != -1) or (len(line) < 2)):
        return
    #Everything Else/SQL Commands
    #For new commands, just add onto the if-else statements and 
    #create it's appropriate function in commands.py
    else:
        if(line.upper().find("CREATE DATABASE ") != -1):
            commands.CreateDatabase(line, cmd)
        elif(line.upper().find("DROP DATABASE ") != -1):
            commands.DropDatabase(line, cmd)
        elif(line.upper().find("USE ") != -1):
            commands.Use(line, cmd)
        elif(line.upper().find("CREATE TABLE ") != -1):
            commands.CreateTable(line, cmd)
        elif(line.upper().find("DROP TABLE ") != -1):
            commands.DropTable(line, cmd)
        elif(line.upper().find("ALTER TABLE ") != -1):
            commands.AlterTable(line, cmd)
        elif((line.upper().find("SELECT ") != -1) and (line.upper().find(" FROM") != -1)):
            commands.SelectFromTable(line, cmd)
        elif(line.upper().find("SELECT ") != -1):
            commands.SelectTable(line, cmd)
        elif((line.upper().find("INSERT ") != -1) and (line.upper().find(" INTO") != -1)):
            commands.InsertIntoTable(line, cmd)
        elif(line.upper().find("UPDATE ") != -1):
            commands.UpdateTable(line, cmd)
        elif(line.upper().find("SET ") != -1):
            commands.SetTable(line, cmd)
        elif((line.upper().find("DELETE ") != -1) and (line.upper().find(" FROM") != -1)):
            commands.DeleteFromTable(line, cmd)
        elif(line.upper().find("FROM ") != -1):
            commands.FromTable(line, cmd)
        elif(line.upper().find("WHERE ") != -1):
            commands.WhereTable(line, cmd)
        else:
            print("!Invalid command found.")
    return

#Main Function
if __name__ == '__main__':
    if(len(sys.argv) < 2):
        exit("!No filename found.")
    cmd = commands.CommandHandler()
    sqlFile = open(str(sys.argv[1]), "r").read().splitlines()
    for line in sqlFile:
        ReadLine(line, cmd)