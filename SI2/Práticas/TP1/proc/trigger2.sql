use SI2_TP1;	
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