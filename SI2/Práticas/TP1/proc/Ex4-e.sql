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
		select @BookingType=BOOKING_TYPE from BOOKING where ID=@BookingID
		
		--get menu from booking	
		if @BookingType=0
			select @idMenu=MENU_ID from NORMAL_BOOKING where BOOKING_ID=@BookingID
		else
			select @idMenu=MENU_ID from EVENT where BOOKING_ID=@BookingID
		
		if @idMenu!=NULL
		begin
			--declare cursor to see courses of a menu
			declare @mycourses int
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
	
	





