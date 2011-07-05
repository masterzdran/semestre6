use SI2_TP1
set dateformat dmy
/*
exec CreateEvent 2,1,'Festa Aniversário','My Birthday Party!','28/05/2011',1;

--TakeIndividualReservation(@CustomerID int, @Date datetime, @MenuID int, @Qtd int)
exec TakeIndividualReservation 1,'01/06/2011',2,2;

--TakeEventReservation(@CustomerID int, @BookingID int)
exec TakeEventReservation 3,1;
exec TakeEventReservation 1,1;
exec TakeEventReservation 3,2;

select * from LOT
select * from SUPPLIERS

*/
/*f*/

declare @suggestion table(
				ID			int,
				SUPPLIER_ID int,
				QTY			decimal(10,3));
insert into @suggestion select * from dbo.SuggestOrder();		

select * from @suggestion;


/*h)*/
--OK
declare @validityTemp_T table(
			ID_INGREDIENT int,
			ID_LOT int,
			VALIDITY	datetime,
			QTY			decimal(10,3))
insert into @validityTemp_T select * from dbo.OutOfValidity();		
select * from @validityTemp_T

select LOT.INGREDIENTS_ID, LOT.VALIDITY from LOT

/*g) falta testar
	exec UpdateStockWithSupplier 1, 1, 1, 5, '15/08/2011', 100, 0, '15/07/2011'
*/



/*i)*/

--OK

declare @suggestionTemp_I table(
			NAME			varchar(30),
			CITY			char(50),
			CONTACT			char(20))
insert into @suggestionTemp_I select * from dbo.SelectClientOnSpecifyCity('Lisboa');
insert into @suggestionTemp_I select * from dbo.SelectClientOnSpecifyCity('Porto');	
select * from @suggestionTemp_I

/*j*/

--OK

declare @MostSales_T table(
			ID				int,
			NAME			varchar(30),
			NUMBER			int,
			TYPE		char(20))
insert into @MostSales_T select * from dbo.MostSaleCourses();
select * from @MostSales_T

/*k*/

--OK

declare @MostSales_T1 table(
			NAME_MENU			varchar(30),
			PROFIT			smallmoney)
insert into @MostSales_T1 select * from dbo.MostProfitMenu();
select * from @MostSales_T1


select distinct COURSES_INGREDIENTS.QTY from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
					  inner join MENU on MENU.ID = NORMAL_BOOKING.MENU_ID
					  inner join MENU_COURSES on MENU_COURSES.MENU_ID = NORMAL_BOOKING.MENU_ID
					  inner join COURSES on MENU_COURSES.COURSES_ID = COURSES.ID
					  inner join COURSES_INGREDIENTS on COURSES.ID = COURSES_INGREDIENTS.COURSES_ID
					  where COURSES_INGREDIENTS.INGREDIENTS_ID = 10
