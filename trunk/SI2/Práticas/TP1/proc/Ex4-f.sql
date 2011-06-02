use SI2_TP1;

/* Ex4 - f)
Produzir a lista de ingredientes em falta com a indicação dos respectivos fornecedores. 
Se um ingrediente tiver mais do que um fornecedr deve ser indicado o que, em média, vende com 
preço mais baixo
*/
if OBJECT_ID('SuggestOrder') IS NOT NULL
	drop procedure SuggestOrder;
go	
create procedure SuggestOrder()
as
	set transaction isolation level serializable
	begin transaction
		declare @stock decimal(10,3), @reserved decimal(10,3), @ingredientID int
		
		--create temp table with total stock (not divided in lots)
		
		--create temp table for suggested order
		
		--get cursor with current stock
		declare ingredients cursor
		for select INGREDIENTS.ID, INGREDIENTS.QTY_RESERVED, LOT.STOCK
				from INGREDIENTS inner join UNIT
					on INGREDIENTES.UNIT_ID=UNIT.ID
					inner join LOT on INGREDIENTS.ID=LOT.INGREDIENTS_ID
						where LOT.STOCK>0
		
		fetch next from ingredients into @ingredientID, @reserved, @stock
		while(@@FETCH_STATUS=0)
			begin						
			--check each ingredient: if stock-reserved is lower than minimum qty then
			--verify wich supplier is cheapeast and add to suggested order
			
			
			
			
			fetch next from ingredients into @ingredientID, @reserved, @stock
			end



		
		close ingredients
		deallocate ingredients
	commit
	
	





