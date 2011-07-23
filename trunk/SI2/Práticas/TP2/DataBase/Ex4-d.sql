use SI2_TP1;

/* Ex4 - d)
Apresentar o valor a pagar num evento gastronómico considerando as respectivas reduções de preço.
Preço por pessoa!
*/
if OBJECT_ID('EventCost') IS NOT NULL
	drop procedure EventCost;
go	
create procedure EventCost(@BookingID int)
as
	begin transaction ISOLATION LEVEL READ COMMITTED
		--verify if there is a Booking with @@BookingID and get number of customers
		declare @qty int, @MenuID int, @final_discount int, @price smallmoney
		select @qty = Booking.QTY from Booking where ID = @BookingID

		--verify where number of customers fits on discount table
		declare @discount int, @upper_limit int
		declare discount cursor
		for select CUSTOMER_QTY, DISCOUNT from EVENT_DISCOUNTS order by CUSTOMER_QTY;
		open discount
		fetch next from discount into @upper_limit, @discount
		while(@@FETCH_STATUS=0)
			begin
			if @qty>@upper_limit
				set @final_discount=@discount
			fetch next from discount into @upper_limit, @discount
			end
		select @MenuID=MENU_ID from EVENT where BOOKING_ID = @BookingID
		select @price=PRICE from MENU where ID=@MenuID
		return (@price - (@price * @final_discount/100))
	commit