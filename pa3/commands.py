#File: Command Handler
#By: Benjamin Estela
#Class: CS 457

#Modules
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
def CreateDatabase(line):
    tableName = line.split(";")[0].lower()
    try:
        os.mkdir(tableName)
        print("Database", tableName, "created.")
    except:
        print("!Failed to create database %s because is already exists." %tableName)

#DROP DATABASE
def DropDatabase(line):
    tableName = line.split(";")[0].lower()
    try:
        os.rmdir(tableName)
        print("Database", tableName, "deleted.")
    except:
        print("!Failed to delete %s because it does not exist." %tableName)

#USE
def Use(line):
    dbName = line.split(";")[0].lower()
    try:
        os.chdir(dbName)
        print("Using database %s." %dbName)
    except:
        try:
            os.chdir("..")
            os.chdir(dbName)
            print("Using database ../%s." %dbName)
        except:
            print("!Cannot access database %s." %dbName)

#CREATE TABLE
def CreateTable(line):
    tableName = line.split(" ")[0].lower()
    paramaters = line.split(" ", 1)[1]
    paramaters = paramaters.strip().replace(";", "").replace(", ", "|")
    paramaters = paramaters[1:-1]
    if not (os.path.exists(tableName)):
        fileName = open(tableName, "w")
        fileName.write(paramaters)
        print("Table %s created." %tableName)
        fileName.close()
    else:
        print("!Failed to create table %s because it already exists." %tableName)

#DROP TABLE
def DropTable(line):
    tableName = line.split(";")[0].lower()
    if os.path.exists(tableName):
        os.remove(tableName)
        print("Table %s deleted." %tableName)
    else:
        print("!Failed to delete %s because it does not exist." %tableName)

#ALTER TABLE
def AlterTable(line):
    tableName = line.split(" ")[0].lower()
    parameters = line.split(" ", 2)[2].replace(";", "").replace(", ", "|")
    if(line.split(" ")[1] == "ADD"):
        if os.path.exists(tableName):
            fileName = open(tableName, "a+")
            fileName.write("|%s" %parameters)
            fileName.close()
            print("Table %s modified." %tableName)
        else:
            print("!Failed to modify table %s because it does not exist." %tableName)

#SELECT * FROM (Query All)
def SelectFromTable(line):
    tableName = line.split(";")[0].lower()
    if os.path.exists(tableName):
        fileName = open(tableName, "r").read().splitlines()
        for each in fileName:
            print(each)
    else:
        print("!Failed to query table %s because it does not exist." %tableName)

#SELECT (Query Specfic)
def SelectTable(line, cmd):
    cmd.PrevSQL = line.split(" ", 1)[1]
    cmd.PrevSQL = cmd.PrevSQL.strip().replace(" ", "").replace(",", "|")
    cmd.DataManipulation = cmdName.SELECT

#INSERT INTO
def InsertIntoTable(line, cmd):
    tableName = line.split(" ")[2].lower()
    paramaters = line.split("(", 1)[1]
    paramaters = paramaters.split(";")[0].replace("\t", "").replace(" ", "").replace("'", "").replace(",","|")
    paramaters = paramaters[:-1]
    if os.path.exists(tableName):
        fileName = open(tableName, "a+")
        fileName.write("\n%s" %paramaters)
        fileName.close()
        print("1 new record inserted.")
    else:
        print("!Failed to insert into table %s because it does not exist." %tableName)

#UPDATE
def UpdateTable(line, cmd):
    tableName = line.split(" ", 1)[1].strip().lower()
    if os.path.exists(tableName):
        cmd.TableName = tableName
        cmd.DataManipulation = cmdName.UPDATE
    else:
        print("!Failed to find table %s because it does not exist." %tableName)

#SET
def SetTable(line, cmd):
    cmd.PrevSQL = line.split(" ", 1)[1]
    cmd.PrevSQL = cmd.PrevSQL.strip().replace("'", "")

#FROM
def FromTable(line, cmd):
    tableName = line.split(" ", 1)[1].strip().lower()
    if os.path.exists(tableName):
        cmd.TableName = tableName
    else:
        print("!Failed to find table %s because it does not exist." %tableName)

#DELETE FROM
def DeleteFromTable(line, cmd):
    tableName = line.split(" ", 2)[2].strip().lower()
    if os.path.exists(tableName):
        cmd.TableName = tableName
        cmd.DataManipulation = cmdName.DELETE
    else:
        print("!Failed to find table %s because it does not exist." %tableName)

#WHERE
def WhereTable(line, cmd):
    if not os.path.exists(cmd.TableName):
        print("!Failed to find table %s because it does not exist." %cmd.TableName)
        return

    #Parse WHERE command
    whereStr = line.split(" ", 1)[1]
    whereStr = whereStr.strip().replace(";", "").replace("'","")

    #Open table for reading
    with open(cmd.TableName, "r") as file:
        data = file.readlines()

    #Set parameters in a list
    firstLine = data[0]
    parametersIndex = firstLine.count(" ")
    firstLine = firstLine.replace("|", " ")
    parameters = [""]
    parameters[0] = firstLine.split(" ")[0]
    for index in range(1, parametersIndex):
        parameters.append(firstLine.split(" ")[index * 2])
    for index in range(len(parameters)):
        if(str(whereStr.split(" ")[0]) == str(parameters[index])):
            parametersIndex = index
        if(str(cmd.PrevSQL.split(" ")[0]) == str(parameters[index])):
            setIndex = index
    count = 0

    #UPDATE only supports "="
    if(cmd.DataManipulation == cmdName.UPDATE):
        if(whereStr.split(" ")[1] == "="):
            for index, each in enumerate(data):
                if(index != 0):
                    if(each.split("|")[parametersIndex] == whereStr.split(" ")[2]):
                        data[index] = each.replace(each.split("|")[setIndex], cmd.PrevSQL.split(" ")[2]) + "\n"
                        count = count + 1
        #Print amount of records (>0) modified
        if(count == 1):
            print("1 record modified.")
        elif(count > 1):
            print("%i records modified." %count)
    #DELETE only suports "=", ">"
    elif(cmd.DataManipulation == cmdName.DELETE):
        if(whereStr.split(" ")[1] == "="):
            for index, each in enumerate(data):
                if(index != 0):
                    if(each.split("|")[parametersIndex] == whereStr.split(" ")[2]):
                        data[index] = ""
                        count = count + 1
        #assumes float values, may need error handling in the future
        elif(whereStr.split(" ")[1] == ">"):
            for index, each in enumerate(data):
                if(index != 0):
                    if(float(each.split("|")[parametersIndex]) > float(whereStr.split(" ")[2])):
                        data[index] = ""
                        count = count + 1
        #Print amount of records (>0) deleted
        if(count == 1):
            print("1 record deleted.")
        elif(count > 1):
            print("%i records deleted." %count)
    #SELECT only supports "!="
    elif(cmd.DataManipulation == cmdName.SELECT):
        queryStr = ""
        if(whereStr.split(" ")[1] == "!="):
            for index, each in enumerate(data):
                if(index != 0):
                    if(each.split("|")[parametersIndex] != whereStr.split(" ")[2]):
                        for x in range(0, cmd.PrevSQL.count("|")+1):
                            for y in range(0, len(parameters)):
                                if(cmd.PrevSQL.split("|")[x] == parameters[y]):
                                    queryStr += each.split("|")[y] + "|"
                                    if(y == len(parameters)):
                                        queryStr += "\n"
            print(data[0].strip())
            print(queryStr[:-1].strip())
    else:
        print("!Invalid use of the WHERE command.")

    with open(cmd.TableName, "w") as file:
        file.writelines(data)

    cmd.TableName = ""
    cmd.PrevSQL = ""
    cmd.DataManipulation = cmdName.NONE
