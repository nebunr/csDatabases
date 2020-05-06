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
    #create its appropriate function in commands.py
    else:
        if(line.upper().find("CREATE DATABASE ") != -1):
            commands.CreateDatabase(line[16:])
        elif(line.upper().find("DROP DATABASE ") != -1):
            commands.DropDatabase(line[14:])
        elif(line.upper().find("USE ") != -1):
            commands.Use(line[4:])
        elif(line.upper().find("CREATE TABLE ") != -1):
            commands.CreateTable(line[13:])
        elif(line.upper().find("DROP TABLE ") != -1):
            commands.DropTable(line[11:])
        elif(line.upper().find("ALTER TABLE ") != -1):
            commands.AlterTable(line[12:])
        elif((line.upper().find("SELECT ") != -1) and (line.upper().find(" FROM ") != -1)):
            if(line.upper().split(" ")[1] == "*"):
                commands.SelectFromTable(line[14:])
        elif(line.upper().find("SELECT ") != -1):
            if(line.upper().split(" ")[1] == "*"):
                commands.SelectTable(line, cmd, 1)
            else:
                commands.SelectTable(line, cmd, 0)
        elif((line.upper().find("INSERT ") != -1) and (line.upper().find(" INTO ") != -1)):
            if(line.upper().split("(")[0].find("VALUES") != -1):
                commands.InsertIntoTable(line, cmd)
        elif(line.upper().find("UPDATE ") != -1):
            commands.UpdateTable(line, cmd)
        elif(line.upper().find("SET ") != -1):
            commands.SetTable(line, cmd)
        elif((line.upper().find("DELETE ") != -1) and (line.upper().find(" FROM ") != -1)):
            commands.DeleteFromTable(line, cmd)
        elif(line.upper().find("FROM ") != -1):
            commands.FromTable(line, cmd)
        elif(line.upper().find("WHERE ") != -1):
            if(cmd.DataManipulation != commands.cmdName.INNER_JOIN):
                commands.WhereTable(line, cmd)
            else:
                commands.OnTable(line, cmd)
        elif(line.upper().find("ON ") != -1):
            commands.OnTable(line, cmd)
        else:
            print("!Invalid command found.")

#Main Function
if __name__ == '__main__':
    try:
        sqlFile = open(str(sys.argv[1]), "r").read().splitlines()
    except:
        exit("!No filename found in command line argument.")
    cmd = commands.CommandHandler()
    for line in sqlFile:
        ReadLine(line, cmd)
