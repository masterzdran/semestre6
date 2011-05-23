use SI2_TP1;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'FRIENDS')
drop table FRIENDS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'MENU_COURSES')
drop table MENU_COURSES;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'COURSES_INGREDIENTS')
drop table COURSES_INGREDIENTS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'ORDERS_LOG')
drop table ORDERS_LOG;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'ORDERS')
drop table ORDERS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'PURCHASES')
drop table PURCHASES;
if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'SUPPLIERS')
drop table SUPPLIERS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'INGREDIENTS')
drop table INGREDIENTS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'EVENT')
drop table EVENT;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'MENU')
drop table MENU;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'BOOKING')
drop table BOOKING;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'REGISTERED')
drop table REGISTERED;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'MEETING')
drop table MEETING;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'COMMENTS')
drop table COMMENTS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'COURSES')
drop table COURSES;	

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'CUSTOMER')
drop table CUSTOMER;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'ADDRESS')
drop table ADDRESS;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'COUNTRY')
drop table COUNTRY;

--USE [master]
--GO

--/****** Object:  Database [SI2_TP1]    Script Date: 05/21/2011 22:09:11 ******/
--IF  EXISTS (SELECT name FROM sys.databases WHERE name = N'SI2_TP1')
--DROP DATABASE [SI2_TP1]
--GO