use SI2_TP1;

/* Ex4 - h)
 Implementar um mecanismo de alarme caso existam ingredientes fora da validade.
*/
if OBJECT_ID('OutOfValidity') IS NOT NULL
	drop function OutOfValidity;
go	

create function OutOfValidity()
returns @validityTemp table(
			ID_ING			int,
			ID_LOT			int,
			VALIDITY	datetime,
			QTY			decimal(10,3))
as
	begin TRANSACTION ISOLATION LEVEL READ COMMITTED
		declare @stock decimal(10,3), @validity datetime, @ingredientID_stock int, @currentDate datetime
		
		declare @ID_ingredient int, @numberOfUnits decimal(10,3)
		
		set @currentDate = GetDate()
		set @numberOfUnits = 0
		
		
		--see all ingredients that had unit's
		--know number of units of this ingredient
		declare ingredients cursor
		for select ID from INGREDIENTS
		open ingredients
		fetch next from ingredients into @ID_ingredient
		while(@@FETCH_STATUS=0)
		begin
			--get units already used by restaurants
			select @numberOfUnits = SUM(COURSES_INGREDIENTS.QTY) from BOOKING
					  inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
					  inner join MENU on MENU.ID = NORMAL_BOOKING.MENU_ID
					  inner join MENU_COURSES on MENU_COURSES.MENU_ID = NORMAL_BOOKING.MENU_ID
					  inner join COURSES on MENU_COURSES.COURSES_ID = COURSES.ID
					  inner join COURSES_INGREDIENTS on COURSES.ID = COURSES_INGREDIENTS.COURSES_ID
					  where COURSES_INGREDIENTS.INGREDIENTS_ID = @ID_ingredient
					  group by COURSES_INGREDIENTS.INGREDIENTS_ID
					  
				--get cursor with lot that have stock
				declare stockcursor cursor
				for select LOT.INGREDIENTS_ID, VALIDITY, QTY
						from LOT 
						where (LOT.INGREDIENTS_ID = @ID_ingredient)
						order by LOT.VALIDITY
				open stockcursor
				fetch next from stockcursor into @ingredientID_stock, @validity, @stock	
				while(@@FETCH_STATUS=0)
					begin
					set @stock = @stock - @numberOfUnits
					-- if @numberOfUnits is negative it means that already verify this ingredient
					if @stock <= 0
					begin
						set @numberOfUnits = 0
						BREAK
					end
					--verify if date isn't valid, if is true we save a tuple in temporary table
					--and break the cicle because we already verify that this ingredient isn't valid
					if @validity < @currentDate AND @stock > 0
						begin
							insert into @validityTemp values(@ID_ingredient, @ingredientID_stock, @validity, @stock)
							BREAK
						end
					fetch next from stockcursor into @ingredientID_stock, @validity, @stock
				end
				close stockcursor
				deallocate stockcursor	
			fetch next from ingredients into @ID_ingredient
		end 
		close ingredients
		deallocate ingredients
		
	return
	end
	
/*	
	select /*NORMAL_BOOKING.MENU_ID, MENU.ID, MENU_COURSES.COURSES_ID, COURSES.ID, COURSES_INGREDIENTS.INGREDIENTS_ID,*/ SUM(COURSES_INGREDIENTS.QTY) from BOOKING
					  inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
					  inner join MENU on MENU.ID = NORMAL_BOOKING.MENU_ID
					  inner join MENU_COURSES on MENU_COURSES.MENU_ID = NORMAL_BOOKING.MENU_ID
					  inner join COURSES on MENU_COURSES.COURSES_ID = COURSES.ID
					  inner join COURSES_INGREDIENTS on COURSES.ID = COURSES_INGREDIENTS.COURSES_ID
					  group by COURSES_INGREDIENTS.INGREDIENTS_ID
	select COURSES_INGREDIENTS.INGREDIENTS_ID, SUM(COURSES_INGREDIENTS.QTY), from BOOKING
					  inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
					  inner join MENU on MENU.ID = NORMAL_BOOKING.MENU_ID
					  inner join MENU_COURSES on MENU_COURSES.MENU_ID = NORMAL_BOOKING.MENU_ID
					  inner join COURSES on MENU_COURSES.COURSES_ID = COURSES.ID
					  inner join COURSES_INGREDIENTS on COURSES.ID = COURSES_INGREDIENTS.COURSES_ID
					  group by COURSES_INGREDIENTS.INGREDIENTS_ID
	
	select * from LOT
	
	*/