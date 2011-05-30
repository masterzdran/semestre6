use SI2_TP1
set nocount on;
set xact_abort on;
set dateformat dmy
go

begin transaction populateTables

--dbo.PREFERENCES(MIN_EVENT_CUSTOMER, MAX_NUMBER_COSTUMERS)
insert into dbo.PREFERENCES(MIN_EVENT_CUSTOMER, MAX_NUMBER_COSTUMERS) values(10, 50);

--dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT)
insert into dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT) values()
go
--dbo.COUNTRY
insert into dbo.COUNTRY(NAME) values ('Portugal');
insert into dbo.COUNTRY(NAME) values ('Espanha');
insert into dbo.COUNTRY(NAME) values ('França');
go
--dbo.ADDRESS
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rua A', 1000, 'Lisboa', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rua B', 1100, 'Lisboa', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rua C', 1200, 'Lisboa', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rua A', 4000, 'Porto', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rua D', 4100, 'Porto', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Avenida A', 2400, 'Leiria', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rua A', 2600, 'Loures', 1);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Calle E', 92900, 'Barcelona', 2);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Calle F', 80000, 'Madrid', 2);
insert into dbo.ADDRESS(STREET,ZIP_CODE,CITY,COUNTRY_ID) values('Rue G', 75000, 'Paris', 3);
go

--dbo.SUPPLIERS
insert into dbo.SUPPLIERS(NAME, ADDRESS_ID) values('Pingo Doce', 1);
insert into dbo.SUPPLIERS(NAME, ADDRESS_ID) values('Armazém A', 2);
insert into dbo.SUPPLIERS(NAME, ADDRESS_ID) values('Quinta', 7);
go
--dbo.UNIT
insert into dbo.UNIT(UNIT) values('kg');
insert into dbo.UNIT(UNIT) values('g');
insert into dbo.UNIT(UNIT) values('l');
insert into dbo.UNIT(UNIT) values('ml');
insert into dbo.UNIT(UNIT) values('uni');
go
--dbo.INGREDIENTS
-- CreateIngredients(@Name char(30), @Qty_reserved int, @Unit int)
CreateIngredients 'Bifes Vazia',0, 5;		--1
go
CreateIngredients 'Azeite',0, 3;			--2
go
CreateIngredients 'Alho', 0, 1;				--3	
go
CreateIngredients 'Batatas',0, 1;			--4
go
CreateIngredients 'Sal', 0, 2;				--5
go
CreateIngredients 'Pimenta', 0, 2;			--6
go
CreateIngredients 'Bacalhau', 0, 1;			--7
go
CreateIngredients 'Leite', 0, 3;			--8
go
CreateIngredients 'Cebola', 0, 1;			--9
go
CreateIngredients 'Natas', 0, 3;			--10
go
CreateIngredients 'Peitos Frango', 0, 5;	--11
go
CreateIngredients 'Cogumelos', 0, 1;		--12
go
CreateIngredients 'Salsa', 0, 2;			--13
go
CreateIngredients 'Ovos', 0, 5;				--14
go

--dbo.COURSES
--CreateCourses(@Name varchar(50), @active bit, @price smallmoney)
CreateCourses 'Peitos Frango com Cogumelos', 1, 10;
go
CreateCourses 'Bacalhau com Natas', 1, 14;
go
CreateCourses 'Bife à Portuguesa', 1, 12;
go

--dbo.COURSES_INGREDIENTS
--JoinCoursesToIngredients(@CoursesID int, @IngredientsID int,@Qtd int)
JoinCoursesToIngredients 1,11,1;
go
JoinCoursesToIngredients 1,12,0.125;
go
JoinCoursesToIngredients 1,13,10;
go
JoinCoursesToIngredients 1,9,0.100;
go
JoinCoursesToIngredients 1,3,0.02;
go
JoinCoursesToIngredients 1,2,0.05;
go
JoinCoursesToIngredients 2,2,0.2;
go
JoinCoursesToIngredients 2,8,0.100;
go
JoinCoursesToIngredients 2,9,0.100;
go
JoinCoursesToIngredients 2,4,0.200;
go
JoinCoursesToIngredients 2,10,0.50;
go
JoinCoursesToIngredients 3,1,0.200;
go
JoinCoursesToIngredients 3,2,0.100;
go
JoinCoursesToIngredients 3,3,0.50;
go
JoinCoursesToIngredients 3,7,0.200;
go

--CreateMenu(@MenuName char(20), @MenuType char(20),@coursesID int)
CreateMenu 'Menu Carne','Carne',3;
go
CreateMenu 'Menu Peixe','Peixe',1;
go
CreateMenu 'Menu Festa','2 Pratos',1;
go
CreateMenu 'Menu Festa','',2;
go

--dbo.CUSTOMER
insert into dbo.CUSTOMER(NAME, CONTACT, CUSTOMER_TYPE) values('Nuno Sousa', '919876543', 0);
insert into dbo.CUSTOMER(NAME, CONTACT, CUSTOMER_TYPE) values('Nuno Cancelo', '911234567', 0);
insert into dbo.CUSTOMER(NAME, CONTACT, CUSTOMER_TYPE) values('Cláudia Crisóstomo', '969876543', 0);

--dbo.REGISTERED
insert into dbo.REGISTERED(CUSTOMER_ID,ADDRESS_ID) values(1,6);
insert into dbo.REGISTERED(CUSTOMER_ID,ADDRESS_ID) values(2,7);
insert into dbo.REGISTERED(CUSTOMER_ID,ADDRESS_ID) values(3,3);

--dbo.FRIENDS
insert into dbo.FRIENDS(REGISTERED_ID1, REGISTERED_ID2) values(1,2);
insert into dbo.FRIENDS(REGISTERED_ID1, REGISTERED_ID2) values(1,3);
insert into dbo.FRIENDS(REGISTERED_ID1, REGISTERED_ID2) values(2,3);
insert into dbo.FRIENDS(REGISTERED_ID1, REGISTERED_ID2) values(3,1);

--CreateEvent(@CustomerID int, @MenuID int, @NameEvent char(20), @Description char(20) , @date datetime, @Qtd int, @BookingType tinyint)

CreateEvent 2,1,'Festa Aniversário','','28-05-2011',1,0


commit

select * from BOOKING
select * from EVENT
select * from EVENT_FRIENDS
select * from FRIENDS
select * from CUSTOMER
select * from REGISTERED
select * from MENU