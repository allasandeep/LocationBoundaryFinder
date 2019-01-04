drop schema if exists z1821331 cascade;

create schema z1821331;

create table z1821331.Region(ID int primary key, IName varchar(50), RType varchar(50),Min_Latitude varchar(10), Max_Latitude varchar(10), Min_Longitude varchar(10), Max_Longitude varchar(10));