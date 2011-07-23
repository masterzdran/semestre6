use SI2_TP1;
/*
Exercice 4 a.
Criar um cardápio com porcoes (quantidade de ingredientes),
precos
e ingredientes consumidos. 
*/
set dateformat dmy;
if OBJECT_ID('CreateCourses') IS NOT NULL
	drop procedure CreateCourses;
go
create procedure CreateCourses(@Name varchar(50), @active bit, @price smallmoney, @type char(20), @idCatalog int)
as
	begin transaction isolation level serializable
		insert into dbo.COURSES values(@Name, @active, @price, @type, @idCatalog);
	commit
go

if OBJECT_ID('CreateIngredients') IS NOT NULL
	drop procedure CreateIngredients;
go
create procedure CreateIngredients(@Name char(30), @Qty_reserved decimal(10,3), @Unit int, 
										 @QtyMin decimal(10,3), @QtyMax decimal(10,3))
as
	begin transaction isolation level serializable
		insert into dbo.INGREDIENTS values(@Name, @Qty_reserved, @Unit, @QtyMin, @QtyMax);
	commit
go

if OBJECT_ID('JoinCoursesToIngredients') IS NOT NULL
	drop procedure JoinCoursesToIngredients;
go
create procedure JoinCoursesToIngredients(@CoursesID int, @IngredientsID int,
											@Qtd decimal(10,3))
as
	begin transaction isolation level serializable
		insert into dbo.COURSES_INGREDIENTS values(@CoursesID, @IngredientsID, @Qtd);
	commit
go

if OBJECT_ID('JoinMenuToCourse') IS NOT NULL
	drop procedure JoinMenuToCourse;
go
create procedure JoinMenuToCourse(@MenuID int, @coursesID int)
as
	set transaction isolation level serializable
	begin transaction
		declare @price smallmoney
		select @price=price from MENU where ID=@MenuID
		set @price += (select price from COURSES where ID=@coursesID)
		update MENU set PRICE=@price where ID=@MenuID
		insert into dbo.MENU_COURSES values(@MenuID, @coursesID)
	commit
go

if OBJECT_ID('CreateMenu') IS NOT NULL
	drop procedure CreateMenu;
go
--we need to insert price of courses, i think that price should be
--in table Menu_Course because price of each courses can be different
create procedure CreateMenu(@MenuName char(30), @MenuType char(30))
as
	set transaction isolation level serializable
	begin transaction
	-- check if menu already exists, if not creates a new one
		if not exists (select ID from Menu where (Menu.NAME = @MenuName))
			insert into dbo.MENU 
				values(@MenuName, 0, @MenuType)
	commit
go


if OBJECT_ID('SetMenuPrice') IS NOT NULL
	drop procedure SetMenuPrice;
go
--this store procedure update price sale to client
create procedure SetBookingPrice(@BookingID int,@price smallmoney)
as
	set transaction isolation level serializable
	begin transaction
		update BOOKING set SALE_PRICE=@price where ID=@BookingID
	commit
go

if OBJECT_ID('JoinMenuToBooking') IS NOT NULL
	drop procedure JoinMenuToBooking;
go
--this store procedure allow us count exactly what is our cost of
--buying allingredients of each courses to suppliers
create procedure JoinMenuToBooking(@BookingID int,@MenuID int)
as
	set transaction isolation level serializable
	begin transaction
		declare @price smallmoney
		select @price=price from MENU where ID=@MenuID
		set @price += (select COST_PRICE from BOOKING where ID=@BookingID)
		update BOOKING set SALE_PRICE=@price where ID=@BookingID
		insert into dbo.NORMAL_BOOKING(BOOKING_ID, MENU_ID)
			values(@BookingID,@MenuID);
	commit
go