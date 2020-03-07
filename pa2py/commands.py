"""
File: Command Handler
By: Benjamin Estela
Class: CS 457
"""

#Header Files
import os

#Enumeration Definition
class cmdName(enumerate):
    NONE = 0
    UPDATE = 1
    DELETE = 2
    SELECT = 3

#Class Definition
class CommandHandler:
    DataManipulation = cmdName.NONE
    TableName = ""
    PrevSQL = ""

#Free Function Definitions

#CREATE DATABASE
def CreateDatabase(line, cmd):
    dbName = line.split(" ")[2]
    dbName = dbName.split(";")[0]
    try:
        os.mkdir(dbName)
        print("Database", dbName, "created.")
    except:
        print("!Failed to create database %s because is already exists." %dbName)
    return

#DROP DATABASE
def DropDatabase(line, cmd):
    dbName = line.split(" ")[2]
    dbName = dbName.split(";")[0]
    try:
        os.rmdir(dbName)
        print("Database", dbName, "deleted.")
    except:
        print("!Failed to delete %s because it does not exist." %dbName)
    return

#USE
def Use(line, cmd):
    dbName = line.split(" ")[1]
    dbName = dbName.split(";")[0]
    try:
        os.chdir(dbName)
        print("Using database %s." %dbName)
    except:
        try:
            os.chdir("..")
            os.chdir(dbName)
            print("Using database ../%s." %dbName)
        except:
            print("!Cannot access datbase %s." %dbName)
    return

#CREATE TABLE
def CreateTable(line, cmd):
    tableName = line.split(" ")[2]
    paramaters = line.split(" ", 3)[3]
    paramaters = paramaters.replace(";", "")
    paramaters = paramaters[1:]
    paramaters = paramaters[:-1]
    paramaters = paramaters.replace(", ", " | ")
    if not (os.path.exists(tableName)):
        fileName = open(tableName, "w")
        fileName.write(paramaters)
        print("Table %s created." %tableName)
    else:
        print("!Failed to create table %s because it already exists." %tableName)
    return

#DROP TABLE
def DropTable(line, cmd):
    tableName = line.split(" ")[2]
    tableName = tableName.split(";")[0]
    if os.path.exists(tableName):
        os.remove(tableName)
        print("Table %s deleted." %tableName)
    else:
        print("!Failed to delete %s because it does not exist." %tableName)
    return

#ALTER TABLE
def AlterTable(line, cmd):
    tableName = line.split(" ")[2]
    parameters = line.split(" ", 4)[4]
    parameters = parameters.replace(";", "")
    parameters = parameters.replace(", ", " | ")
    if(line.split(" ")[3] == "ADD"):
        if os.path.exists(tableName):
            fileName = open(tableName, "a+")
            fileName.write(" | %s" %parameters)
            print("Table %s modified." %tableName)
        else:
            print("!Failed to modify table %s because it does not exist." %tableName)
    return

#SELECT * FROM (Query All)
def SelectFromTable(line, cmd):
    tableName = line.split(" ")[3]
    tableName = tableName.split(";")[0]
    if(line.upper().find(" * ") != -1):
        if os.path.exists(tableName):
            fileName = open(tableName, "r").read().splitlines()
            for each in fileName:
                print(each)
        else:
            print("!Failed to query table %s because it does not exist." %tableName)
    return

#SELECT (Query Specfic)
def SelectTable(line, cmd):
    return

#INSERT INTO
def InsertIntoTable(line, cmd):
    return

#UPDATE
def UpdateTable(line, cmd):
    return

#SET
def SetTable(line, cmd):
    return

#FROM
def FromTable(line, cmd):
    return

#WHERE
def WhereTable(line, cmd):
    return

#DELETE FROM
def DeleteFromTable(line, cmd):
    return