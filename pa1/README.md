# CS 457 PA1: Metadata Management

## By: Benjamin Estela (2/20/2020)

### Overview
This is a C++ program that manages metadata of an .sql script.   

The current functionalities include:
- Database creation, delection  
- Table creation, deletion, update, and query  

This program strictly runs through a filename-argument interface such that in order to run, users must give a proper file name (see below). A design document `name.txt` is included that clarifies how the program organizes multiple databases, manages multiple tables, and how it is all implemented.

### Instructions (Linux/Ubuntu)
Unzip the given `bestela_pa1.zip` source code then navigate to where it has been extracted.

To build:
```bash
$ make
```

To run:
```bash
$ ./pa PA1_test.sql
```
