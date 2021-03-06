#!/usr/bin/env python3

#File: Main Python3 File
#By: Benjamin Estela
#Class: CS 457

#Header Files
import commands
#Modules
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
            commands.CreateDatabase(line)
        elif(line.upper().find("DROP DATABASE ") != -1):
            commands.DropDatabase(line)
        elif(line.upper().find("USE ") != -1):
            commands.Use(line)
        elif(line.upper().find("CREATE TABLE ") != -1):
            commands.CreateTable(line)
        elif(line.upper().find("DROP TABLE ") != -1):
            commands.DropTable(line)
        elif(line.upper().find("ALTER TABLE ") != -1):
            commands.AlterTable(line)
        elif((line.upper().find("SELECT ") != -1) and (line.upper().find(" FROM") != -1)):
            commands.SelectFromTable(line)
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