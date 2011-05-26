use SI2_TP1;
/*
Exercice 4 b.
Criar um evento gastronomico.
*/

if OBJECT_ID('CreateEvent') IS NOT NULL
	drop procedure CreateEvent;
go

create procedure CreateEvent(@CustomerID int, @MenuID int,@NameEvent char(20), 
				@Description char(20) , @date datetime, @Qtd int, @BookingType tinyint)
as
	begin transaction
	--create a new event with the owner(customer)
		insert into dbo.Booking(CUSTOMER_ID, DATE,QTY,BOOKING_TYPE)
			values(@CustomerID, @date, @Qtd, @BookingType);
		--see if there is a function that gives the last identity of
		--a specify table 
		declare @BookingID int
		set @BookingID = 0
		select @BookingID = ID from Booking where
			(Booking.Customer_ID = @CustomerID AND Booking.Date = @date AND
				Booking.Qty = @Qtd)
	--and menu choosed by him
		insert into event values(@BookingID, @MenuID, @NameEvent);		
	commit