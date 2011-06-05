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

declare @suggestion table(
				ID			int,
				SUPPLIER_ID int,
				QTY			decimal(10,3));
insert into @suggestion select * from dbo.SuggestOrder();		

select * from @suggestion;
*/

/*h)

declare @validityTemp_T table(
			ID_INGREDIENT int,
			ID_LOT int,
			VALIDITY	datetime,
			QTY			decimal(10,3))
insert into @validityTemp_T select * from dbo.OutOfValidity();		
select * from @validityTemp_T
*/

/*g) falta testar*/

/*i)*/

declare @suggestionTemp_I table(
			NAME			varchar(30),
			CITY			char(50),
			CONTACT			char(20))
insert into @suggestionTemp_I select * from dbo.SelectClientOnSpecifyCity('Lisboa');
insert into @suggestionTemp_I select * from dbo.SelectClientOnSpecifyCity('Porto');	
select * from @suggestionTemp_I

/*j*/

declare @MostSales_T table(
			ID				int,
			NAME			varchar(30),
			NUMBER			int,
			TYPE		char(20))
insert into @MostSales_T select * from dbo.MostSaleCourses();
select * from @MostSales_T

/*k*/

declare @MostSales_T1 table(
			NAME_MENU			varchar(30),
			PROFIT			smallmoney)
insert into @MostSales_T1 select * from dbo.MostProfitMenu();
select * from @MostSales_T1