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
create procedure CreateIngredients(@Name char(30), @Qty_reserved int, @Unit int)
as
	begin transaction
		insert into dbo.INGREDIENTS values(@Name, @Qty_reserved, @Unit);
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
	begin transaction
		insert into dbo.MENU_COURSES values(@MenuID, @coursesID);
	commit
go

if OBJECT_ID('CreateMenu') IS NOT NULL
	drop procedure CreateMenu;
go
--we need to insert price of courses, i think that price should be
--in table Menu_Course because price of each courses can be different
create procedure CreateMenu(@MenuName char(20), @MenuType char(20),
							@coursesID int)
as
	begin transaction
	-- check if menu already exists, if not creates a new one
		if not exists (select ID from Menu where (Menu.NAME = @MenuName))
			insert into dbo.MENU values(@MenuName, @MenuType)
		
		-- get the MenuID from table
		declare @MenuID int
		select @MenuID = ID from Menu where (Menu.Name = @MenuName)
	--insert a new menu_courses
		exec JoinMenuToCourse @MenuID, @coursesID
	commit
go
