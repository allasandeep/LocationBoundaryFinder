/***************************************************************************************
CSCI 511          Program     Fall 2018

Programmer: Sandeep Alla(z1821331)

Date Due: December 07 2018, Monday 11:59 PM

Purpose: This program inserts the data into the tables and retrieves the boundaries of the inputed name
 ****************************************************************************************/
#include<iostream>
#include<postgresql/libpq-fe.h>

//Methods from standard library
using std::cerr;
using std::cout;
using std::endl;

//Function to delete spaces in a char array
void delSpaces(char *str)
{
	int count = 0;
	//Looping the char array and searching fro empty space
	for(int i = 0; str[i]; i++)
	{
		if(str[i] != ' ')
			str[count++] = str[i];
	}

	str[count] = '\0';
}

//Function to establish connection to the database
PGconn* conn()
{
	//Connecting to the Database with user credentials
	PGconn *db = PQconnectdb("host = 'courses' dbname = 'z1821331' user = 'z1821331'  password = '1996Jun06' ");
	//If the connection fails, print an error message
	if(!(CONNECTION_OK == PQstatus(db)))
	{
		cerr<<"Can't connect to db."<<endl;
		exit(EXIT_FAILURE);
	}
	cout<<"Database Connection Successfull!"<<endl;

	return db;;
}
