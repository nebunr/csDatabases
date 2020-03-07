"""
File: Command Handler
By: Benjamin Estela
Class: CS 457
"""

#Header Files
import os
import array as arr

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
def CreateDatabase(line):
    dbName = line.split(" ")[2]
    dbName = dbName.split(";")[0]
    try:
        os.mkdir(dbName)
        print("Database", dbName, "created.")
    except:
        print("!Failed to create database %s because is already exists." %dbName)
    return

#DROP DATABASE
def DropDatabase(line):
    dbName = line.split(" ")[2]
    dbName = dbName.split(";")[0]
    try:
        os.rmdir(dbName)
        print("Database", dbName, "deleted.")
    except:
        print("!Failed to delete %s because it does not exist." %dbName)
    return

#USE
def Use(line):
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
def CreateTable(line):
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
        fileName.close()
    else:
        print("!Failed to create table %s because it already exists." %tableName)
    return

#DROP TABLE
def DropTable(line):
    tableName = line.split(" ")[2]
    tableName = tableName.split(";")[0]
    if os.path.exists(tableName):
        os.remove(tableName)
        print("Table %s deleted." %tableName)
    else:
        print("!Failed to delete %s because it does not exist." %tableName)
    return

#ALTER TABLE
def AlterTable(line):
    tableName = line.split(" ")[2]
    parameters = line.split(" ", 4)[4]
    parameters = parameters.replace(";", "")
    parameters = parameters.replace(", ", "|")
    if(line.split(" ")[3] == "ADD"):
        if os.path.exists(tableName):
            fileName = open(tableName, "a+")
            fileName.write("|%s" %parameters)
            fileName.close()
            print("Table %s modified." %tableName)
        else:
            print("!Failed to modify table %s because it does not exist." %tableName)
    return

#SELECT * FROM (Query All)
def SelectFromTable(line):
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
    cmd.PrevSQL = line.split(" ", 1)[1]
    cmd.PrevSQL = cmd.PrevSQL.strip()
    cmd.PrevSQL = cmd.PrevSQL.replace(" ", "")
    cmd.PrevSQL = cmd.PrevSQL.replace(",", "|")
    cmd.DataManipulation = cmdName.SELECT
    return

#INSERT INTO
#TODO: Issue with single quotes
def InsertIntoTable(line, cmd):
    tableName = line.split(" ")[2]
    paramaters = line.split(" ", 3)[3]
    paramaters = paramaters.split(";")[0]
    paramaters = paramaters.replace("\t", "")
    paramaters = paramaters.replace(" ", "")
    #paramaters = paramaters.replace("'", "")
    if(paramaters.upper().split("(")[0] == "VALUES"):
        paramaters = paramaters.split("(")[1]
        paramaters = paramaters[:-1]
        paramaters = paramaters.replace(",", "|")
        if os.path.exists(tableName):
            fileName = open(tableName, "a+")
            fileName.write("\n%s" %paramaters)
            fileName.close()
            print("1 new record inserted.")
        else:
            print("!Failed to insert into table %s because it does not exist." %tableName)
    return

#UPDATE
def UpdateTable(line, cmd):
    tableName = line.split(" ", 1)[1]
    tableName = tableName.strip()
    if os.path.exists(tableName):
        cmd.TableName = tableName
        cmd.DataManipulation = cmdName.UPDATE
    else:
        print("!Failed to find table %s because it does not exist." %tableName)
    return

#SET
def SetTable(line, cmd):
    cmd.PrevSQL = line.split(" ", 1)[1]
    cmd.PrevSQL = cmd.PrevSQL.strip()
    return

#FROM
def FromTable(line, cmd):
    tableName = line.split(" ", 1)[1]
    tableName = tableName.strip()
    if os.path.exists(tableName):
        cmd.TableName = tableName
    else:
        print("!Failed to find table %s because it does not exist." %tableName)
    return

#DELETE FROM
def DeleteFromTable(line, cmd):
    tableName = line.split(" ", 2)[2]
    tableName = tableName.strip()
    if os.path.exists(tableName):
        cmd.TableName = tableName
        cmd.DataManipulation = cmdName.DELETE
    else:
        print("!Failed to find table %s because it does not exist." %tableName)
    return

#WHERE
#TODO: AT LEAST PYTHON IS NICE
def WhereTable(line, cmd):
    whereStr = line.split(" ", 1)[1]
    whereStr = whereStr.strip()
    whereStr = whereStr.replace(";", "")
    if not os.path.exists(cmd.TableName):
        print("!Failed to find table %s because it does not exist." %cmd.TableName)
        return


    fileName = open(cmd.TableName, "r+")


    #firstLine = fileName.readline()
    #parametersCount = firstLine.count(" ") + 1
    #parameters = ["0", "1", "2", "3", "4"]
    #parameters[0] = firstLine.split(" ")[0]
    #for x in range(1, parametersCount - 1):
    #    parameters[x] = firstLine.split(" ")[x]




    if(cmd.DataManipulation == cmdName.UPDATE):
        if(whereStr.split(" ")[1] == "="):
            for each in fileName:
                if(each.find(whereStr.split(" ")[2]) != -1):
                    print("WE DID IT")
                    #fileName.write(line.replace(whereStr.split(" ")[2]))
        #cmd.PrevSQL.split(" ")[2]
        #for each in fileName:
            #if(line.find(whereStr))
        #print("UPDATE")
    elif(cmd.DataManipulation == cmdName.DELETE):
        print("DELETE")
    elif(cmd.DataManipulation == cmdName.SELECT):
        print("SELECT")
    else:
        print("!Invalid use of the WHERE command.")
    fileName.close()
    cmd.TableName = ""
    cmd.PrevSQL = ""
    cmd.DataManipulation = ""
    return