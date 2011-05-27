use SI2_TP1;

/* Ex4 - e)
Cativar o stock de ingredientes na sequência da confirmação das reservas. 
*/
if OBJECT_ID('ConfirmAReservation') IS NOT NULL
	drop procedure ConfirmAReservation;
go	
create procedure ConfirmAReservation(@BookingID int, @CustomerID int)
as
	begin transaction
		--updating status of reservation of event given by parameter
		update dbo.EVENT_FRIENDS set EVENT_FRIENDS.STATUS = 1
			where (BOOKING_ID = @BookingID AND CUSTOMER_ID = @CustomerID)
		--verify if booking is an event
		declare @idMenu int, @mycourses int, @myingredients int, @qtd_ing int
		set @idMenu = -1
		set @mycourses = -1
		set @myingredients = -1
		set @qtd_ing = -1
		select @idMenu=MENU_ID from EVENT where BOOKING_ID = @BookingID
		if @idMenu > -1
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
			fetch next from myingredients into @myingredients, @qtd_ing
				declare @qtdr int
				set @qtdr = 0
				select @qtdr = QTY_RESERVED from INGREDIENTS where ID = @myingredients
				set @qtdr += @qtd_ing
				update dbo.Ingredients set Ingredients.QTY_RESERVED = @qtdr
						where Ingredients.ID = @myingredients
			close myingredients
			
			close mycourses	
		end
	commit