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
create procedure CreateCourses(@Name varchar(50), @active bit, @price smallmoney)
as
	begin transaction
		insert into dbo.COURSES values(@Name, @active, @price);
	commit
go

if OBJECT_ID('CreateIngredients') IS NOT NULL
	drop procedure CreateIngredients;
go
create procedure CreateIngredients(@Name char(30), @current decimal(10,3), @Qty_reserved decimal(10,3), @Unit int, 
										 @QtyMin decimal(10,3), @QtyMax decimal(10,3))
as
	begin transaction
		insert into dbo.INGREDIENTS values(@Name, @current, @Qty_reserved, @Unit, @QtyMin, @QtyMax);
	commit
go

if OBJECT_ID('JoinCoursesToIngredients') IS NOT NULL
	drop procedure JoinCoursesToIngredients;
go
create procedure JoinCoursesToIngredients(@CoursesID int, @IngredientsID int,
											@Qtd decimal(10,3))
as
	begin transaction
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
create procedure CreateMenu(@MenuName char(30), @MenuType char(30),
							@coursesID int)
as
	set transaction isolation level serializable
	begin transaction
	-- check if menu already exists, if not creates a new one
		if not exists (select ID from Menu where (Menu.NAME = @MenuName))
			insert into dbo.MENU 
				values(@MenuName, (select PRICE from COURSES where ID=@coursesID), @MenuType)
		
		-- get the MenuID from table
		declare @MenuID int
		select @MenuID = ID from Menu where (Menu.Name = @MenuName)
	--insert a new menu_courses
		exec JoinMenuToCourse @MenuID, @coursesID
	commit
go


if OBJECT_ID('SetMenuPrice') IS NOT NULL
	drop procedure SetMenuPrice;
go
--we need to insert price of courses, i think that price should be
--in table Menu_Course because price of each courses can be different
create procedure SetMenuPrice(@MenuID int,@price smallmoney)
as
	set transaction isolation level serializable
	begin transaction
		update MENU set PRICE=@price where ID=@MenuID
	commit
go