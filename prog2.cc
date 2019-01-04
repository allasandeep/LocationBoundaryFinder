/***************************************************************************************
CSCI 511          Program     Fall 2018

Programmer: Sandeep Alla(z1821331)

Date Due: December 07 2018, Monday 11:59 PM

Purpose: This program inserts the data into the tables and retrieves the boundaries of the inputed name
 ****************************************************************************************/
#include "prog2.h"
#include "functions.cc"

int main()
{
	string regionName = "";
	PGconn *db;
	db = conn();
	cout<<"Enter the Region Name: ";
	//Reading the user input
	std::getline(cin,regionName);
	//Calling the getRegionData by passing regionName and db connection
	getRegionData(regionName,db);

	PQfinish(db);
	return 0;
}

void getRegionData(string str, PGconn *db)
{
	char query[100];
	char temp[str.length() + 1];
	//Converting the string to lowercase
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	//Copying the string to char*
	strcpy(temp , str.c_str());
	//Deleting the spacing in the char*
	delSpaces(temp);
	PGresult * result = nullptr;
	//Psql Query by concatinating with c++ variables
	sprintf(query,"select *from region where lower(iname) = '%s';",temp);
	//Executing the query and storing the result in result.
	result = PQexec(db,query);
	//Number of tuples in the result
	int nrows = PQntuples(result);

	//Checking 
	if( PGRES_TUPLES_OK != PQresultStatus(result)) 
	{
		//Error	
		cerr << "Query is not successfull" << endl;
		cerr << PQresultErrorMessage(result) << endl;
	}

	if(nrows > 0)
	{
		for(int r = 0; r < nrows; r++)
		{			
			string sID(PQgetvalue(result,r,0));
			int stateId = stoi(sID.substr(0,2));
			char queryTemp[50];
			PGresult * resultTemp = nullptr;
			//Psql Query by concatinating with c++ variables
			sprintf(queryTemp,"select iname from region where id = %d;",stateId);
			//Executing the query and storing the result in result.
			resultTemp = PQexec(db,queryTemp);
			string stateName = PQgetvalue(resultTemp,0,0);
			PQclear(resultTemp);
			string outputString = toDecimalDegree(PQgetvalue(result, r, 0),PQgetvalue(result, r, 1),PQgetvalue(result, r, 3),PQgetvalue(result, r, 4),PQgetvalue(result, r, 5),PQgetvalue(result, r, 6), stateName);
			cout<<outputString<<endl;
			cout<<endl;
		}
	}
	else
		cout<<"No tuples found with the given name"<<endl;

	//Clearing the result
	PQclear(result);
}

//Function to convert the decimal degree into Degree, Minute and second notation
//It takes id, iname, minLatitude, maxLatitude, minLongitude and maxLongitude as parameters
//This function returns the output string to be displayed
string toDecimalDegree(char *id, char *iname, char *minLatitude, char *maxLatitude, char *minLongitude, char* maxLongitude, string stateName)
{	
	string output = "The place of ";
	output += iname;
	output += ", ";
	output += stateName;
	output += " (ID: ";
	output += id;
	output += ") has the bounds \n";

	//If the minLongitude is not empty
	if(minLongitude)
	{
		string temp(minLongitude);
		output += formatOutputString(stoi(temp.substr(1)));	
	}

	output += "to ";
	//If the maxLongitude is not empty
	if(maxLongitude)
	{
		string temp(maxLongitude);		
		output += formatOutputString(stoi(temp.substr(1)));			
	}

	if(minLongitude[0] == '+' && maxLongitude[0] == '+')
		output += "east " ;
	else if(minLongitude[0] == '-' && maxLongitude[0] == '-')	
		output += "west " ; 

	output += "in longitude;\nand from ";

	//If the minLatitude is not empty
	if(minLatitude)
	{
		string temp(minLatitude);
		output += formatOutputString(stoi(temp.substr(1)));	
	}

	output += "to ";

	//If the maxLatitude is not empty
	if(maxLatitude)
	{
		string temp(maxLatitude);
		output += formatOutputString(stoi(temp.substr(1)));		
	}

	if(minLatitude[0] == '+' && maxLatitude[0] == '+')
		output += "north " ;
	else if(minLatitude[0] == '-' && maxLatitude[0] == '-')	
		output +=  "south "; 

	output += "in latitude.";
	//Returning the output
	return output;	
}

string formatOutputString(int boundary)
{
	double dd;
	int d = 0, m = 0;
	float value = 0, seconds = 0;
	string sTemp = "",s = "", outString = "";	
	dd = (double)boundary/ (double)1000000;
	//Formula to convert to DMS
	d = dd;
	m = (dd-d) * 60;
	value = (dd-(double)d - ((double)m/(double)60))*3600;
	seconds = roundf(value * 100)/100;
	sTemp = to_string(seconds);
	s = sTemp.substr(0,sTemp.length()-4);
	//Appendning the DMS values to the string as to be displayed
	outString += to_string(d);
	outString += " degrees, "; 
	outString += to_string(m); 
	outString += " minutes, "; 
	outString += s;
	outString += " seconds ";

	return outString;
}
