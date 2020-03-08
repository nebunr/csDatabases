#File: Command Handler
#By: Benjamin Estela
#Class: CS 457

#Header Files
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
            print("!Cannot access database %s." %dbName)
    return

#CREATE TABLE
def CreateTable(line):
    tableName = line.split(" ")[2]
    paramaters = line.split(" ", 3)[3]
    paramaters = paramaters.strip().replace(";", "").replace(", ", "|")
    paramaters = paramaters[1:-1]
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
    parameters = parameters.replace(";", "").replace(", ", "|")
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
    cmd.PrevSQL = cmd.PrevSQL.strip().replace(" ", "").replace(",", "|")
    cmd.DataManipulation = cmdName.SELECT
    return

#INSERT INTO
def InsertIntoTable(line, cmd):
    tableName = line.split(" ")[2]
    paramaters = line.split(" ", 3)[3]
    paramaters = paramaters.split(";")[0].replace("\t", "").replace(" ", "").replace("'", "")
    if(paramaters.upper().split("(")[0] == "VALUES"):
        paramaters = paramaters.split("(")[1].replace(",", "|")
        paramaters = paramaters[:-1]
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
    cmd.PrevSQL = cmd.PrevSQL.strip().replace("'", "")
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
    return