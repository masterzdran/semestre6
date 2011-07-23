use SI2_TP1
/*Ex4 - j)
	Listar as porções individuais mais vendidas agrupados por tipo (entrada, prato, sobremesa, …)
*/
if OBJECT_ID('MostSaleCourses') IS NOT NULL
	drop function MostSaleCourses;
go	

create function MostSaleCourses()
returns @MostSales table(
			ID				int,
			NAME			varchar(30),
			NUMBER			int,
			TYPE		char(20))
as
	begin TRANSACTION ISOLATION LEVEL READ COMMITTED
		--put all courses in temporary table
		insert into @MostSales 
			select MENU_COURSES.COURSES_ID, COURSES.NAME, COUNT(*) as Total, COURSES.TYPE
		from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
		inner join MENU_COURSES on NORMAL_BOOKING.MENU_ID = MENU_COURSES.MENU_ID
		inner join COURSES on COURSES.ID = MENU_COURSES.COURSES_ID
		where STATUS = 1
		GROUP BY MENU_COURSES.COURSES_ID, COURSES.NAME, COURSES.TYPE
	return
	end
--create a temporary table with all courses and type of 

/*
select * from MENU
select * from BOOKING
select * from NORMAL_BOOKING
select * from MENU_COURSES

select NORMAL_BOOKING.BOOKING_ID, NORMAL_BOOKING.MENU_ID, MENU_COURSES.COURSES_ID
		from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
		inner join MENU_COURSES on NORMAL_BOOKING.MENU_ID = MENU_COURSES.MENU_ID
 where STATUS = 1

select MENU_COURSES.COURSES_ID, COUNT(*) as Total 
		from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
		inner join MENU_COURSES on NORMAL_BOOKING.MENU_ID = MENU_COURSES.MENU_ID
 where STATUS = 1
 GROUP BY MENU_COURSES.COURSES_ID
 
select MENU_COURSES.COURSES_ID, COURSES.NAME, COUNT(*) as Total, COURSES.TYPE
		from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
		inner join MENU_COURSES on NORMAL_BOOKING.MENU_ID = MENU_COURSES.MENU_ID
		inner join COURSES on COURSES.ID = MENU_COURSES.COURSES_ID
 where STATUS = 1
 GROUP BY MENU_COURSES.COURSES_ID, COURSES.NAME, COURSES.TYPE

-- uma tentativa falhada de ordenar decrescentemente o TotalSales dentro do tipo...
select T.COURSES_ID, T.NAME,MAX(T.TotalSales) as TotalSales, T.TYPE  from
	( select MENU_COURSES.COURSES_ID, COURSES.NAME, COUNT(*) as TotalSales, COURSES.TYPE
			from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
			inner join MENU_COURSES on NORMAL_BOOKING.MENU_ID = MENU_COURSES.MENU_ID
			inner join COURSES on COURSES.ID = MENU_COURSES.COURSES_ID
	 where STATUS = 1
	 GROUP BY MENU_COURSES.COURSES_ID, COURSES.NAME, COURSES.TYPE) as T
 GROUP BY T.TYPE,T.COURSES_ID,T.NAME, TotalSales, T.TYPE
 ORDER BY T.TYPE desc
*/
