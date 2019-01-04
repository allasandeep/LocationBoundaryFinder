/***************************************************************************************
CSCI 511          Program     Fall 2018

Programmer: Sandeep Alla

Date Due: December 07 2018, Monday 11:59 PM

Purpose: This program inserts the data into the tables and retrieves the boundaries of the inputed name
****************************************************************************************/
#ifndef guard
#define guard
#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include<postgresql/libpq-fe.h>
#include<stdlib.h>
#include<cctype>
#include<math.h>

//Required methods from standard library
using std::cerr;
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::endl;
using std::to_string;

//Functions
void openFiles( ifstream& , char * );
void processBoundFiles( ifstream&, PGconn * );
void processNameFiles( ifstream&, PGconn * );
void closeFiles( ifstream& );
#endif
