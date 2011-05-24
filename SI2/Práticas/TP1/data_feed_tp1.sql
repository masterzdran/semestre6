use SI2_TP1
set nocount on;
set xact_abort on;
set dateformat dmy;
go

begin transaction populateTables

--dbo.COUNTRY
insert into dbo.COUNTRY(ID, NAME) values (1,'Portugal');
insert into dbo.COUNTRY(ID, NAME) values (2,'Espanha');
insert into dbo.COUNTRY(ID, NAME) values (3,'França');
insert into dbo.COUNTRY(ID, NAME) values (4,'Inglaterra');

--dbo.ADDRESS
insert into dbo.ADDRESS(ID,STREET,ZIP_CODE,CITY,COUNTRY_ID) values();

--dbo.SUPPLIERS
insert into dbo.SUPPLIERS(ID, NAME, ADDRESS_ID) values();

--dbo.INGREDIENTS
insert into dbo.INGREDIENTS(ID, NAME, DESCRIPTION, QTY, QTY_RESERVED, VALUE) values();

--dbo.COURSES
insert into dbo.COURSES(ID, NAME, VALUE, ACTIVE) values();

--dbo.COURSES_INGREDIENTS
insert into dbo.COURSES_INGREDIENTS(COURSES_ID, INGREDIENTS_ID, QTY) values();

--dbo.CUSTOMER
insert into dbo.CUSTOMER(ID, NAME, CONTACT, CUSTOMER_TYPE, ADDRESS_ID) values();

--dbo.REGISTERED
insert into dbo.REGISTERED(CUSTOMER_ID,ADDRESS_ID) values();

--dbo.FRIENDS
insert into dbo.FRIENDS(REGISTERED_ID1, REGISTERED_ID2) values();

--dbo.MENU
insert into dbo.MENU(ID, NAME, TYPE) values();

--dbo.MENU_COURSES
insert into dbo.MENU_COURSES(MENU_ID, COURSES_ID);