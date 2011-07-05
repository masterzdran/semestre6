use SI2_TP1;
-- se for marcada reserva no estado confirmado reserva ingredientes se existir Menu (reservas normais)
-- se for alterado estado de reserva para confirmado reserva ingredientes
-- se for alterado estado de reserva para cancelado, cancela reserva de ingredientes

IF EXISTS(SELECT * FROM sys.objects WHERE type = 'TR' AND name = 'trigger_Booking')
	DROP TRIGGER trigger_Booking
go

create trigger trigger_Booking
	on dbo.BOOKING
	for update
	as
		declare @old_status tinyint, @new_status tinyint, @n int, @n1 int, @bookingID int, @Qty int
		set transaction isolation level serializable
		
		begin transaction
		
		select @bookingID = ID from inserted
		select @Qty = QTY from inserted
		select @n = count(*) from inserted
		select @n1 = count(*) from deleted
		
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
