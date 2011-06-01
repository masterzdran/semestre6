use SI2_TP1;
/*
delete from PREFERENCES;
delete from EVENT_FRIENDS;
delete from FRIENDS;
delete from MENU_COURSES;
delete from COURSES_INGREDIENTS;
delete from ORDERS_LOG;
delete from ORDERS;
delete from LOT;
delete from SUPPLIERS;
delete from INGREDIENTS;
delete from UNIT;
delete from NORMAL_BOOKING;
delete from EVENT;
delete from MENU;
delete from BOOKING;
delete from REGISTERED;
delete from MEETING;
delete from COMMENTS;
delete from COURSES;	
delete from CUSTOMER;
delete from ADDRESS;
delete from COUNTRY;
*/

if OBJECT_ID('PREFERENCES') IS NOT NULL
  drop table PREFERENCES;

if OBJECT_ID('EVENT_DISCOUNTS') IS NOT NULL
  drop table EVENT_DISCOUNTS;
  
if OBJECT_ID('EVENT_FRIENDS') IS NOT NULL
  drop table EVENT_FRIENDS;
  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  
if OBJECT_ID('PREFERENCES') IS NOT NULL  


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
		where TABLE_NAME = 'LOT')
drop table LOT;
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
		where TABLE_NAME = 'UNIT')
drop table UNIT;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'NORMAL_BOOKING')
drop table NORMAL_BOOKING;

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