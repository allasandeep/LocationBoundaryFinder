/***************************************************************************************
CSCI 511          Program     Fall 2018

Programmer: Sandeep Alla(z1821331)

Date Due: December 07 2018, Monday 11:59 PM

Purpose: This program inserts the data into the tables and retrieves the boundaries of the inputed name
 ****************************************************************************************/
#include "prog1.h"
#include "functions.cc"

//Main 
int main(int argc, char* argv[])
{
	//File Stream object
	ifstream is;
	PGconn *db; 
	db = conn();
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			//Calling open_files function by passing input file stream objects as arguments.
			openFiles(is,argv[i]); 
			string str(argv[i]);
			string toFind = ".RTC";
			//Finding whether the file contains the bnd extension
			size_t found = str.find(toFind);
			//If the file contains bnd extension go to processBoundFiles or go to processNameFiles
			if(found != string::npos)
				processNameFiles(is,db);//Calling processBoundFiles function by passing input file stream objects as arguments.
			//Calling closeFiles function by passing input file stream objects as arguments.
			closeFiles(is);
		}

		for(int i = 1; i < argc; i++)
		{
			//Calling open_files function by passing input file stream objects as arguments.
			openFiles(is,argv[i]); 
			string str(argv[i]);
			string toFind = ".bnd";
			//Finding whether the file contains the bnd extension
			size_t found = str.find(toFind);
			//If the file contains bnd extension go to processBoundFiles or go to processNameFiles
			if(found != string::npos)
				processBoundFiles(is,db);//Calling processBoundFiles function by passing input file stream objects as arguments.
			//Calling closeFiles function by passing input file stream objects as arguments.
			closeFiles(is);
		}
	}
	else
	{
		cerr<<"**Note: Please input data files as commad line arguments to insert data into database!"<<endl;
		return 0;
	}

	cout<<"Data Successfully inserted into the database!"<<endl;
	PQfinish(db);
	return 0;
}

//Function to openFiles
void openFiles( ifstream& is, char *fileName)
{
	// opening the input file. 
	is.open(fileName);
	// If the file fails to open,then displays an error message. 
	if(is.fail()) 
	{
		cerr<<"Error Message:: Unable to read" <<fileName<< endl;
		exit(EXIT_FAILURE);
	}		
}

//Function to process bound files
void processBoundFiles(ifstream& is, PGconn *db)
{
	//Required Variables
	string line;	
	int id = 0;
	string minLatitude = "";
	string minLongitude = "";
	string maxLatitude = "";
	string maxLongitude = "";

	//Reading data from file line by line 
	while(std::getline(is,line))
	{
		//Getting the substrings and putting them into the respective variables
		id = stoi(line.substr(0,7));
		minLongitude = line.substr(7,10);
		minLatitude = line.substr(17,9);
		maxLongitude = line.substr(26,10);
		maxLatitude = line.substr(36,9);	        
		char query[150];
		//Converting all the string variables into char *
		char min_longitude[minLongitude.length()+1];
		strcpy(min_longitude, minLongitude.c_str());
		char min_latitude[minLatitude.length()+1];
		strcpy(min_latitude, minLatitude.c_str());
		char max_longitude[maxLongitude.length()+1];
		strcpy(max_longitude, maxLongitude.c_str());
		char max_latitude[maxLatitude.length()+1];
		strcpy(max_latitude, maxLatitude.c_str());
		PGresult * result = nullptr;
		//Psql Query by concatinating with c++ variables
		sprintf(query,"update region set min_latitude = '%s' ,max_latitude = '%s' ,min_longitude = '%s' ,max_longitude = '%s' where id = %d;", min_latitude, max_latitude, min_longitude, max_longitude, id);
		//Executing the query and storing the result in result.
		result = PQexec(db,query);
		//Clearing the result
		PQclear(result);   
	}	

}

//Function to process Name files
void processNameFiles(ifstream& is, PGconn *db)
{
	//Required Variable declarations
	string line = "";
	string state_id = "";
	string county_id = "";
	string place_id = "";
	string region_type = "";
	string name = "";
	string year = "";
	int Id = 0;
	string type = "";
	bool insert_flag = false;
	char r_type;

	//Reading data from file line by line 
	while(std::getline(is,line))
	{
		//Getting the substrings and putting them into the respective variables
		insert_flag = false;
		state_id = line.substr(5,2);
		county_id = state_id + line.substr(7,3);
		year = line.substr(10,4);
		place_id = state_id + line.substr(14,5);
		region_type = line.substr(24,1); 
		name = line.substr(52,60);
		r_type = region_type[0];

		if( year == "2000" || year == "    ")
		{
			//Depending upon the type of region the ID and type variables are set and setting the insert_flag to true
			switch(r_type)
			{
				case 'S':
					type = "State";
					//checking whether the state length is 2
					if(state_id.length() == 2)
					{
						Id = stoi(state_id);
						insert_flag = true;
					}
					break;
				case 'C':
					type = "County";
					//checking whether the countyid length is 5
					if(county_id.length() == 5)
					{
						Id = stoi(county_id);
						insert_flag = true;
					}
					break;
				case 'M':
					type = "Subcounty";
					//checking whether the subcounty length is 7
					if(place_id.length() == 7)
					{
						Id = stoi(place_id);
						insert_flag = true;	      
					}
				case 'P':
					type = "Place";
					//checking whether the placeid length is 5
					if(place_id.length() == 7)
					{
						Id = stoi(place_id);
						insert_flag = true;
					}
			}

			PGresult * result = nullptr;
			//Psql Query by concatinating with c++ variables
			string query = "select id from region;";
			//Executing the query and storing the result in result.
			result = PQexec(db,query.c_str());
			//Number of tuples in the result
			int nrows = PQntuples(result);
			bool alreadyExits = false;

			if(nrows > 0)
			{
				for(int r = 0; r < nrows; r++)
				{
					if(PQgetvalue(result, r, 0) == to_string(Id))
					{
						alreadyExits = true;
					}
				}
			}	
					
			//Clearing the result
			PQclear(result);

			//If the insert flag is true then insert the data into database region
			if(insert_flag && !alreadyExits)
			{
				char query[100];
				char c_name[name.length()+1];
				strcpy(c_name, name.c_str());
				delSpaces(c_name);
				char c_type[type.length()+1];
				strcpy(c_type, type.c_str());

				//Psql Query by concatinating with c++ variables
				sprintf(query,"insert into region(id,iname,rtype) values(%d,'%s','%s');", Id, c_name, c_type);
				//Executing the query and storing the result in result.
				result = PQexec(db,query);

				//Clearing the result
				PQclear(result);			
			}
		}	
	}

}

//Function to close the files
void closeFiles ( ifstream& is)
{	
	// closing the Bound input file.
	is.close();     
}
