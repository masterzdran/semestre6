use SI2_TP1;

/* Ex4 - h)
 Implementar um mecanismo de alarme caso existam ingredientes fora da validade.
*/
if OBJECT_ID('OutOfValidity') IS NOT NULL
	drop function OutOfValidity;
go	

create function OutOfValidity()
returns @validityTemp table(
			ID			int,
			VALIDITY	datetime,
			QTY			decimal(10,3))
as
	begin
		declare @stock decimal(10,3), @validity datetime, @ingredientID int, @currentDate datetime
		set @currentDate = GetDate()
		
		--get cursor with lot that have stock
		declare stock cursor
		for select LOT.INGREDIENTS_ID, VALIDITY, STOCK
				from LOT 
				where (LOT.STOCK>0)
				order by LOT.VALIDITY
		open stock
		fetch next from stock into @ingredientID, @validity, @stock	
		while(@@FETCH_STATUS=0)
			begin
			if @validity > @currentDate
			begin
				insert into @validityTemp values(@ingredientID, @validity, @stock)
				
			end
									
			fetch next from stock into @ingredientID, @validity, @stock
			end
			
		close stock
		deallocate stock
	return
	end
	
/*	
select LOT.INGREDIENTS_ID, VALIDITY, STOCK
				from LOT 
				where (LOT.STOCK>0)
				order by LOT.VALIDITY
*/



