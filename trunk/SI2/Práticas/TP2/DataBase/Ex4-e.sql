use SI2_TP1;

/* Ex4 - e)
Cativar o stock de ingredientes na sequência da confirmação das reservas. 
*/
if OBJECT_ID('CaptivateIngredients') IS NOT NULL
	drop procedure CaptivateIngredients;
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
/*
	while(@@FETCH_STATUS=0)
		begin
		insert into dbo.EVENT_FRIENDS(BOOKING_ID, CUSTOMER_ID, STATUS) values(@BookingID, @FriendID, 0)
		fetch next from c into @FriendID
		end
*/		
		if @idMenu!=0
		begin
			--declare cursor to see courses of a menu
			declare @mycourses int
			declare mycourses cursor
			for select COURSES_ID from MENU_COURSES where MENU_ID = @idMenu;
			open mycourses
			fetch next from mycourses into @mycourses
			while(@@FETCH_STATUS=0)
				begin
				--declare a cursor to see ingredients of each courses
				declare myingredients cursor
				for select INGREDIENTS_ID, QTY from COURSES_INGREDIENTS where COURSES_ID = @mycourses;
				open myingredients
				declare @myingredients int, @qtd_ing decimal(10,3)
				fetch next from myingredients into @myingredients, @qtd_ing
				while(@@FETCH_STATUS=0)
					begin
					declare @qtdr decimal(10,3)
					set @qtdr = 0
					select @qtdr = QTY_RESERVED from INGREDIENTS where ID = @myingredients
					set @qtdr += @qtd_ing
					update dbo.Ingredients set Ingredients.QTY_RESERVED = @qtdr
						where Ingredients.ID = @myingredients
					fetch next from myingredients into @myingredients, @qtd_ing
					end
				fetch next from mycourses into @mycourses
				end
		close myingredients
		deallocate myingredients
		close mycourses	
		deallocate mycourses
		end

	commit
	
	





