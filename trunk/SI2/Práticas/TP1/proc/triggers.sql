use SI2_TP1;
-- se for marcada reserva no estado confirmado reserva ingredientes se existir Menu (reservas normais)
-- se for alterado estado de reserva para confirmado reserva ingredientes
-- se for alterado estado de reserva para cancelado, cancela reserva de ingredientes

IF EXISTS(SELECT * FROM sys.objects WHERE type = 'TR' AND name = 'trigger_Booking')
	DROP TRIGGER trigger_Booking
go

create trigger trigger_Booking
	on dbo.BOOKING
	for insert, update
	as
		declare @old_status tinyint, @new_status tinyint, @n int, @n1 int, @bookingID int, @Qty int
		set transaction isolation level serializable
		
		begin transaction
		
		select @bookingID = ID from inserted
		select @Qty = QTY from inserted
		select @n = count(*) from inserted
		select @n1 = count(*) from deleted
		
		-- inserted new line
		if @n>0 and @n1=0
			begin
			select @new_status = status from inserted
			-- only execute if confirmed: normal booking
			if @new_status = 1
				exec CaptivateIngredients @bookingID, @Qty
			end
		-- status updated! booking gets confirmed or cancelled
		if (Update(STATUS))
			begin
			select @new_status = status from inserted
			select @old_status = status from deleted
			-- if confirmed from pending
			if @new_status = 1 and @old_status = 0
				exec CaptivateIngredients @bookingID, @Qty			
				--if cancelled from confirmed
			else if @new_status = 2 and @old_status = 1
				begin
				set @Qty = @Qty * -1
				exec CaptivateIngredients @bookingID, @Qty	
				end
			end
		commit
		
-- sempre que uma reserva indvidual para evento é confirmada verifica se evento está confirmado:
-- se estiver confirmado: reserva ingredientes para essa reserva
-- se não estiver confirmado: verifica se nº reservas individuais é suficiente para reservar evento

IF EXISTS(SELECT * FROM sys.objects WHERE type = 'TR' AND name = 'trigger_Event_Friends')
	DROP TRIGGER trigger_Event_Friends
go

create trigger trigger_Event_Friends
	on dbo.EVENT_FRIENDS
	for update
	as
		declare @new_status int, @old_status int, @bookingID int, @qty int
		set transaction isolation level serializable
		
		begin transaction
		if (Update(STATUS))
			begin
			select @new_status = status from inserted
			select @old_status = status from deleted			
			if @new_status=1 and @old_status=0
				begin
				select @bookingID=BOOKING_ID from inserted
				select @qty = QTY from BOOKING where (ID=@BookingID)
				set @qty +=1
				update BOOKING
					set QTY=@qty
					where (ID = @BookingID)
				/*select @total = sum(STATUS) from dbo.EVENT_FRIENDS
					where BOOKING_ID=@bookingID*/
				if @qty>=(select MIN_EVENT_CUSTOMER from dbo.PREFERENCES)
					update BOOKING set STATUS=1
						where ID=@bookingID
				end
			end
		commit