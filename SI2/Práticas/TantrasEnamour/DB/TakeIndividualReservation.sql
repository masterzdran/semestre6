use SI2_TP1;

/*
c.
Aceitar reservas individuais ou para um evento gastronůmico.
*/

if OBJECT_ID('TakeIndividualReservation') IS NOT NULL
	drop procedure TakeIndividualReservation;
go	
create procedure TakeIndividualReservation(@CustomerID int, @Date datetime, @MenuID int, @Qty int)
as

	begin transaction
		insert into dbo.BOOKING(CUSTOMER_ID, DATE, QTY, BOOKING_TYPE, STATUS)
			values (@CustomerID, @Date, @Qty, 0, 1)

		declare @BookingID int
		set @BookingID = @@IDENTITY

		insert into dbo.NORMAL_BOOKING(BOOKING_ID, MENU_ID)
			values (@BookingID, @MenuID)
		--normal reservation with Menu -> captivate ingredients

		if @MenuID!=0
			exec CaptivateIngredients @bookingID, @Qty
	commit
go	
if OBJECT_ID('TakeEventReservation') IS NOT NULL
	drop procedure TakeEventReservation;
go

create procedure TakeEventReservation(@CustomerID int, @BookingID int)
as
	begin transaction
	
		--if event booking status was Confirmed prior to this individual confirmation then
		--we need to add ingredients to reserved after confirming reservation
		declare @BookingStatus int, @count int
		set @BookingStatus = (select STATUS from BOOKING where ID= @BookingID)

		if exists (select CUSTOMER_ID from EVENT_FRIENDS 
					where (BOOKING_ID = @BookingID and CUSTOMER_ID = @CustomerID and STATUS=0))
			update EVENT_FRIENDS 
				set EVENT_FRIENDS.STATUS=1 
				where(BOOKING_ID = @BookingID and CUSTOMER_ID = @CustomerID)
	commit