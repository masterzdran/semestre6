use SI2_TP1;

/* Ex4 - d)
Apresentar o valor a pagar num evento gastronómico considerando as respectivas reduções de preço.
*/
if OBJECT_ID('EventCost') IS NOT NULL
	drop procedure EventCost;
go	
create procedure EventCost(@BookingID int)
as
	begin transaction
		--verify if there is a Booking with @MenuID
		declare @qtdd int
		set @qtdd = 0
		select @qtdd = Booking.Qty from dbo.Booking where  ID = @MenuID
		set @qtdd += @Qtd
		update dbo.Booking set Booking.Qty = @qtdd where ID = @MenuID
	commit