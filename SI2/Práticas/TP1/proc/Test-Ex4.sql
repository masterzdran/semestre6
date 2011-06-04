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



declare @validityTemp_T table(
			ID_INGREDIENT int,
			ID_LOT int,
			VALIDITY	datetime,
			QTY			decimal(10,3))
insert into @validityTemp_T select * from dbo.OutOfValidity();		
select * from @validityTemp_T

