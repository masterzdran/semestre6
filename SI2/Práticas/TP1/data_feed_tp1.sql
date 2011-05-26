use SI2_TP1
set nocount on;
set xact_abort on;
set dateformat dmy
go

begin transaction populateTables

--dbo.PREFERENCES(MIN_EVENT_CUSTOMER)
insert into dbo.PREFERENCES(MIN_EVENT_CUSTOMER) values(10);

--dbo.COUNTRY
insert into dbo.COUNTRY(NAME) values ('Portugal');
insert into dbo.COUNTRY(NAME) values ('Espanha');
insert into dbo.COUNTRY(NAME) values ('França');

--dbo.ADDRESS
insert into dbo.ADDRESS(ID,STREET,ZIP_CODE,CITY,COUNTRY_ID) values();

--dbo.SUPPLIERS
insert into dbo.SUPPLIERS(ID, NAME, ADDRESS_ID) values();

--dbo.INGREDIENTS
-- CreateIngredients(@Name char(30), @Description char(50), @Qty int, @Qty_reserved int, @price smallmoney)
CreateIngredients 'Batatas','', 0, 0, 0;
CreateIngredients 'Bifanas','', 0, 0, 0;
CreateIngredients 'Arroz','', 0, 0, 0;
CreateIngredients 'Bacalhau','', 0, 0, 0;
CreateIngredients 'Natas','', 0, 0, 0;
CreateIngredients 'Cebolas','', 0, 0, 0;
CreateIngredients 'Alface','', 0, 0, 0;
CreateIngredients 'Tomate','', 0, 0, 0;

--dbo.COURSES
--CreateCourses(@Name varchar(50), @active bit, @price smallmoney)
CreateCourses 'Bitoque', 1, 7;
CreateCourses 'Bacalhau com Natas', 1, 10;

select * from COURSES
select * from INGREDIENTS
--dbo.COURSES_INGREDIENTS
--JoinCoursesToIngredients(@CoursesID int, @IngredientsID int,@Qtd int)
JoinCoursesToIngredients 1,1,0.1;
JoinCoursesToIngredients 1,2,0.2;


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