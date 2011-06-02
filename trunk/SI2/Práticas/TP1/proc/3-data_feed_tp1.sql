use SI2_TP1
set nocount on;
set xact_abort on;
set dateformat dmy
go

begin transaction populateTables

--dbo.PREFERENCES(MIN_EVENT_CUSTOMER, MAX_NUMBER_COSTUMERS)
insert into dbo.PREFERENCES(MIN_EVENT_CUSTOMER, MAX_NUMBER_CUSTOMERS) values(2, 50);

--dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT)
insert into dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT) values(2, 2);
insert into dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT) values(5, 5);
insert into dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT) values(10, 10);
insert into dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT) values(15, 15);
insert into dbo.EVENT_DISCOUNTS(CUSTOMER_QTY, DISCOUNT) values(20, 20);


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
-- CreateIngredients(@Name char(30), @Qty_reserved int, @Unit int, @Min_Qty, @ORDER_QTY)
exec CreateIngredients 'Bifes Vazia',0, 5, 5, 10;		--1
exec CreateIngredients 'Azeite',0, 3, 1, 10;			--2
exec CreateIngredients 'Alho', 0, 1, 0.100, 1;			--3	
exec CreateIngredients 'Batatas',0, 1, 5, 20;			--4
exec CreateIngredients 'Sal', 0, 2, 100, 1000;			--5
exec CreateIngredients 'Pimenta', 0, 2, 50, 200;		--6
exec CreateIngredients 'Bacalhau', 0, 1, 3, 10;			--7
exec CreateIngredients 'Leite', 0, 3, 3, 12;			--8
exec CreateIngredients 'Cebola', 0, 1, 3, 5;			--9
exec CreateIngredients 'Natas', 0, 3, 2, 4;				--10
exec CreateIngredients 'Peitos Frango', 0, 5, 10, 20;	--11
exec CreateIngredients 'Cogumelos', 0, 1, 0.500, 1;		--12
exec CreateIngredients 'Salsa', 0, 2, 100, 300;			--13
exec CreateIngredients 'Ovos', 0, 5, 12, 36;			--14

--dbo.COURSES
--CreateCourses(@Name varchar(50), @active bit, @price smallmoney)
exec CreateCourses 'Peitos Frango com Cogumelos', 1, 10;
exec CreateCourses 'Bacalhau com Natas', 1, 14;
exec CreateCourses 'Bife à Portuguesa', 1, 12;


--dbo.COURSES_INGREDIENTS
--JoinCoursesToIngredients(@CoursesID int, @IngredientsID int,@Qtd int)
exec JoinCoursesToIngredients 1,11,1;
exec JoinCoursesToIngredients 1,12,0.125;
exec JoinCoursesToIngredients 1,13,10;
exec JoinCoursesToIngredients 1,9,0.100;
exec JoinCoursesToIngredients 1,3,0.02;
exec JoinCoursesToIngredients 1,2,0.05;
exec JoinCoursesToIngredients 2,2,0.2;
exec JoinCoursesToIngredients 2,8,0.100;
exec JoinCoursesToIngredients 2,9,0.100;
exec JoinCoursesToIngredients 2,4,0.200;
exec JoinCoursesToIngredients 2,10,0.50;
exec JoinCoursesToIngredients 3,1,0.200;
exec JoinCoursesToIngredients 3,2,0.100;
exec JoinCoursesToIngredients 3,3,0.50;
exec JoinCoursesToIngredients 3,7,0.200;


--CreateMenu(@MenuName char(20), @MenuType char(20),@coursesID int)
exec CreateMenu 'Menu Carne','Carne',3;
exec CreateMenu 'Menu Peixe','Peixe',1;
exec CreateMenu 'Menu Festa','2 Pratos',1;
exec CreateMenu 'Menu Festa','',2;


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

--create procedure CreateEvent(@CustomerID int, @MenuID int,@NameEvent char(20), 
				--@Description char(20) , @date datetime, @Qtd int)

commit

set dateformat dmy
exec CreateEvent 2,1,'Festa Aniversário','My Birthday Party!','28/05/2011',1;

--TakeIndividualReservation(@CustomerID int, @Date datetime, @MenuID int, @Qtd int)
exec TakeIndividualReservation 1,'01/06/2011',2,2;

--TakeEventReservation(@CustomerID int, @BookingID int)
exec TakeEventReservation 3,1;
exec TakeEventReservation 1,1;
exec TakeEventReservation 3,2;


set dateformat dmy
insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(1, 1, 1, '02/06/2011', 5, 10, '15/06/2011', 0);
insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(1, 1, 1, '02/06/2011', 5, 8, '15/06/2011', 0);
insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(1, 1, 1, '02/06/2011', 5, 12,'15/06/2011', 0);
insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(1, 2, 1, '02/06/2011', 5, 15,'15/06/2011', 0);
insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(1, 3, 1, '02/06/2011', 5, 5,'15/06/2011', 0);
insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(2, 3, 1, '02/06/2011', 5, 5,'15/06/2011', 0);


declare @suggestion table(
				ID			int,
				SUPPLIER_ID int,
				QTY			decimal(10,3));
insert into @suggestion select * from dbo.SuggestOrder();		

select * from @suggestion;



select * from BOOKING
select * from EVENT
select * from EVENT_FRIENDS
select * from FRIENDS
select * from CUSTOMER
select * from REGISTERED
select * from MENU
select * from MENU_COURSES
select * from COURSES
select * from COURSES_INGREDIENTS
select * from INGREDIENTS inner join UNIT on (INGREDIENTS.UNIT_ID=UNIT.ID)

