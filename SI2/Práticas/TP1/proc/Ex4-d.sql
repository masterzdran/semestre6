use SI2_TP1;

/* Ex4 - d)
Apresentar o valor a pagar num evento gastronómico considerando as respectivas reduções de preço.
*/
if OBJECT_ID('EventCost') IS NOT NULL
	drop procedure EventCost;
go	
create function EventCost(@BookingID int)
as
	begin transaction
		--verify if there is a Booking with @MenuID and get number of customers
		declare @qty int, @MenuID int, @final_discount int
		set @qty = Booking.Qty from dbo.Booking where  ID = @MenuID

		--verify where number of customers fits on discount table
		declare @discount int, @upper_limit int
		declare discount cursor
		for select CUSTOMER_QTY, DISCOUNT from EVENT_DISCOUNTS;
		open discount
		fetch next from discount into @upper_limit, @discount
		while(@@FETCH_STATUS=0)
			begin
			if @qty>@upper_limit
				set @final_discount=@discount
			fetch next from discount into @upper_limit, @discount
			end
		return @final_discount
	commit