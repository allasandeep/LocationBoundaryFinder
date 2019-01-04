# BoundaryFinder

The Admin is allowed to load in data files through command line arguments. Each entry in a data file is examined to see if it is already
in the database. If it is, it will be ignored.

A separate program (Prog2.cc) asks the user for a region name. After looking up this name, all regions having this name are printed with their bounds Degree Minute Second notation.

Output :  The place of DeKalb, Illinois (ID: 1719161) has the bounds 88 degrees, 47 minutes, 49.43 seconds to 88 degrees, 42 minutes, 3.15 seconds west in longitude;and from 41 degrees, 53 minutes, 11.34 seconds to 41 degrees, 58 minutes, 18.09 seconds north in latitude.

Steps to setup:
1. Run the Scriptfile.sql in your sql to create the database schema.
2. Run Prog1.cc with the data files included in the commad line arguments ( I included few data files like most real world data ). This will process the data and insert them into the database.
3. Run Prog2.cc, this will ask the user to enter a region name. Later gives the boundary values for the regions with that name.
