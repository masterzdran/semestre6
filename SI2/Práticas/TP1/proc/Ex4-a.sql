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
create procedure CreateIngredients(@Name char(30), @Description char(50),
									@Qty int, @Qty_reserved int, @price smallmoney)
as
	begin transaction
		insert into dbo.INGREDIENTS values(@Name, @Description, @Qty, @Qty_reserved,
										@price);
	commit
go

if OBJECT_ID('JoinCoursesToIngredients') IS NOT NULL
	drop procedure JoinCoursesToIngredients;
go
create procedure JoinCoursesToIngredients(@CoursesID int, @IngredientsID int,
											@Qtd int)
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
							@bookingID int, @coursesID int)
as
	begin transaction
	--insert a new menu
		insert into dbo.MENU values(@MenuName, @MenuType);
		--see if there is a function that gives the last identity of
		--a specify table 
		declare @MenuID int
		select @MenuID = ID from Menu where (Menu.Name = @MenuName)
	--insert a new menu_courses
		exec JoinMenuToCourse @MenuID, @coursesID
	commit
go
