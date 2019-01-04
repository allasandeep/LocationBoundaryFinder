#ifndef guard
#define guard
#include<iostream>
#include<cstring>
#include<string>
#include<postgresql/libpq-fe.h>
#include<stdlib.h>
#include<cctype>
#include<math.h>
#include<algorithm>

//Required methods from standard library
using std::cerr;
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::to_string;

//Functions
string toDecimalDegree(char *, char *, char *, char *, char *, char *,string);
void getRegionData(string, PGconn *);
string formatOutputString(int);
#endif
