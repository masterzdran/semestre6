use SI2_TP1;

/*
c.
Aceitar reservas individuais ou para um evento gastronómico.
*/
/*
if OBJECT_ID('TakeIndividualReservationAndEvent') IS NOT NULL
	drop procedure TakeIndividualReservationAndEvent;
go	
create procedure TakeIndividualReservationAndEvent(@MenuID int, @Qtd int)
as
	begin transaction
		--verify if there is a Booking with @MenuID
		declare @qtdd int
		set @qtdd = 0
		select @qtdd = Booking.Qty from dbo.Booking where  ID = @MenuID
		set @qtdd += @Qtd
		--verify if statement of update is right!!!!!!!!!!!!!!!!!
		update dbo.Booking set Booking.Qty = @qtdd where ID = @MenuID
	commit
	*/
if OBJECT_ID('TakeIndividualReservation') IS NOT NULL
	drop procedure TakeIndividualReservation;
go	
create procedure TakeIndividualReservation(@CustomerID int, @Date datetime, @MenuID int, @Qtd int)
as
	begin transaction
		insert into dbo.BOOKING(CUSTOMER_ID, DATE, QTY, BOOKING_TYPE, STATUS)
			values (@CustomerID, @Date, @Qtd, 0, 1)

		declare @BookingID int
		set @BookingID = @@IDENTITY
		/*select @BookingID = ID from BOOKING where
			(BOOKING.Customer_ID = @CustomerID AND BOOKING.Date = @date AND
				BOOKING.Qty = @Qtd)*/

		insert into dbo.NORMAL_BOOKING(BOOKING_ID, MENU_ID)
			values (@BookingID, @MenuID)
		
		-- falta reservar ingredientes para este booking apenas se Menu for !=0

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
		-- criar triger para sempre que é adicionada confirmação de reserva individual para verificar se atigiu
		-- valor mínimo da mesma e se sim para validar evento, e se evento estava válido reservar ingredientes
		-- criar triger para que quando estado da reserva seja alterado de pendente para confirmado para 
		-- reservar ingeredientes

	commit