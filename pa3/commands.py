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
    SELECT_STAR = 4
    INNER_JOIN = 5
    LEFT_OUTER_JOIN = 6

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
    tableName = line.split("(")[0].lower().strip()
    paramaters = line.split("(", 1)[1]
    paramaters = paramaters.strip().replace(";", "").replace(", ", "|")
    paramaters = paramaters[:-1]
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

#SELECT * FROM (Query Table)
def SelectFromTable(line):
    tableName = line.split(";")[0].lower()
    if os.path.exists(tableName):
        fileName = open(tableName, "r").read().splitlines()
        for each in fileName:
            print(each)
    else:
        print("!Failed to query table %s because it does not exist." %tableName)

#SELECT (Query Specific)
def SelectTable(line, cmd, star):
    if(bool(star) == False):
        cmd.PrevSQL = line.split(" ", 1)[1]
        cmd.PrevSQL = cmd.PrevSQL.strip().replace(" ", "").replace(",", "|")
        cmd.DataManipulation = cmdName.SELECT
    else:
        cmd.PrevSQL = ""
        cmd.DataManipulation = cmdName.SELECT_STAR

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
    if(cmd.DataManipulation == cmdName.SELECT):
        tableName = line.split(" ", 1)[1].strip().lower()
        if os.path.exists(tableName):
            cmd.TableName = tableName
        else:
            print("!Failed to find table %s because it does not exist." %tableName)
    elif(cmd.DataManipulation == cmdName.SELECT_STAR):
        if(line.upper().find(",") != -1):
            cmd.PrevSQL = line.lower().split(" ", 1)[1].strip().replace(", ", "|")
            cmd.DataManipulation = cmdName.INNER_JOIN
        elif(line.upper().find("INNER JOIN") != -1):
            cmd.PrevSQL = line.lower().split(" ", 1)[1].strip().replace(" inner join ", "|")
            cmd.DataManipulation = cmdName.INNER_JOIN
        elif(line.upper().find("LEFT OUTER JOIN") != -1):
            cmd.PrevSQL = line.lower().split(" ", 1)[1].strip().replace(" left outer join ", "|")
            cmd.DataManipulation = cmdName.LEFT_OUTER_JOIN
        else:
            print("!Table join type not found in line containing from.")
    else:
        print("!Query type not specified.")

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

#ON
def OnTable(line, cmd):
    #INNER JOIN only supports "=""
    if(cmd.DataManipulation == cmdName.INNER_JOIN):
        line = line.lower().split(" ",1)[1].replace(";", "").strip()
        if(line.find("=") != -1):
            line = line.replace(" ", "")
        else:
            print("!Unsupported operation found in INNER JOIN.")
            return

        table1 = cmd.PrevSQL.split(" ", 1)[0]
        var1 = cmd.PrevSQL.split("|", 1)[0].split(" ", 1)[1]
        table2 = cmd.PrevSQL.split("|", 1)[1].split(" ", 1)[0]
        var2 = cmd.PrevSQL.split("|", 1)[1].split(" ", 1)[1]

        param1 = line.split("=",1)[0].split(".")[1]
        param2 = line.split("=",1)[1].split(".")[1]

        if(((line.split("=")[0].split(".")[0] == var1) and (line.split("=")[1].split(".")[0] == var2)) or (line.split("=")[0].split(".")[0] == var2) and (line.split("=")[1].split(".")[0] == var1)):
            if(line.split("=")[0].split(".")[0] == var2) and (line.split("=")[1].split(".")[0] == var1):
                paramTemp = param1
                param1 = param2
                param2 = paramTemp
        else:
            print("!Unexpected variables used in WHERE or ON line.")
            return
        
        if not os.path.exists(table1):
            print("!Failed to find table %s because it does not exist." %table1)
            return

        if not os.path.exists(table2):
            print("!Failed to find table %s because it does not exist." %table2)
            return

        #Open table for reading
        with open(table1, "r") as file:
            data1 = file.readlines()
        with open(table2, "r") as file:
            data2 = file.readlines()

        firstLine = data1[0].strip() + "|" + data2[0].strip()
        for index in range(data1[0].count("|")):
            if(data1[0].split("|")[index].find(param1) != 1):
                index1 = index
        for index in range(data2[0].count("|")):
            if(data2[0].split("|")[index].find(param2) != 1):
                index2 = index

        dataJoin = ""
        for index, each1 in enumerate(data1):
            for index, each2 in enumerate(data2):
                if(index != 0):
                    if(each1.split("|")[index1] == each2.split("|")[index2]):
                        dataJoin += each1.strip() + "|" + each2.strip() + "\n"
        print(firstLine)
        print(dataJoin.strip())

        #print(table1, "+", table2, "+", var1, "+", var2, "+", param1, "+", param2)

    #OUTER JOIN
    elif(cmd.DataManipulation == cmdName.LEFT_OUTER_JOIN):
        print("ON: LEFT OUTER JOIN")
    else:
        print("!Invalid use of the ON command.")
    return