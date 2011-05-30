use SI2_TP1;

/* Ex4 - e)
Cativar o stock de ingredientes na sequência da confirmação das reservas. 
*/
if OBJECT_ID('ConfirmAReservation') IS NOT NULL
	drop procedure ConfirmAReservation;
go	
create procedure CaptivateIngredients(@BookingID int, @Qty int)
as
	set transaction isolation level serializable
	begin transaction
		declare @idMenu int, @BookingType int
		
		--check type of booking
		select @BookingType from BOOKING where ID=@BookingID
		
		--get menu from booking	
		if @BookingID=0
			select @idMenu from NORMAL_BOOKING where BOOKING_ID=@BookingID
		else
			select @idMenu from EVENT where BOOKING_ID=@BookingID
		
		if @idMenu!=NULL
		begin
			--declare cursor to see courses of a menu
			declare mycourses cursor
			for select COURSES_ID from MENU_COURSES where MENU_ID = @idMenu;
			open mycourses
			fetch next from mycourses into @mycourses
		
			--declare a cursor to see ingredients of each courses
		
			declare myingredients cursor
			for select INGREDIENTS_ID, QTY from COURSES_INGREDIENTS where COURSES_ID = @mycourses;
			open myingredients
			declare @myingredients int, @qtd_ing int
			fetch next from myingredients into @myingredients, @qtd_ing
				declare @qtdr int
				set @qtdr = 0
				select @qtdr = QTY_RESERVED from INGREDIENTS where ID = @myingredients
				set @qtdr += @qtd_ing
				update dbo.Ingredients set Ingredients.QTY_RESERVED = @qtdr
					where Ingredients.ID = @myingredients
		
		
		end
		close myingredients
		deallocate myingredients
		close mycourses	
		deallocate mycourses

	commit
	
	
-- TRIGGERS ON TABLES

-- sempre que uma reserva indvidual para evento é confirmada verifica se evento está confirmado:
-- se estiver confirmado: reserva ingredientes para essa reserva
-- se não estiver confirmado: verifica se nº reservas individuais é suficiente para reservar evento




-- se for marcada reserva no estado confirmado reserva ingredientes se existir Menu (reservas normais)
-- se for alterado estado de reserva para confirmado reserva ingredientes
-- se for alterado estado de reserva para cancelado, cancela reserva de ingredientes

create trigger trigger_Event
	on dbo.BOOKING
	for insert, update
	as
		declare @old_status tinyint, @new_status tinyint, @n int, @n1 int, @bookingID int, @Qty int
		set transaction isolation level serializable
		
		begin transaction
		
		select @bookingID = BOOKING_ID from inserted
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