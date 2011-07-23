use SI2_TP1;

/* Ex4 - f)
Produzir a lista de ingredientes em falta com a indicação dos respectivos fornecedores. 
Se um ingrediente tiver mais do que um fornecedr deve ser indicado o que, em média, vende com 
preço mais baixo
*/
if OBJECT_ID('SuggestOrder') IS NOT NULL
	drop function SuggestOrder;
go	

create function SuggestOrder()
returns @suggestionTemp table(
			ID			int,
			SUPPLIER_ID int,
			QTY			decimal(10,3))
as
	begin transaction ISOLATION LEVEL SERIALIZABLE
		declare @stock decimal(10,3), @reserved decimal(10,3), @ingredientID int
		
		--get cursor with current stock
		declare ingredients cursor
		for select INGREDIENTS.ID, INGREDIENTS.QTY_RESERVED
				from INGREDIENTS 
		open ingredients
		fetch next from ingredients into @ingredientID, @reserved		
		while(@@FETCH_STATUS=0)
			begin
			select @stock = sum(STOCK) from LOT where LOT.INGREDIENTS_ID=@ingredientID
			if @stock is null
				set @stock=0
			--check each ingredient: if stock-reserved is lower than minimum qty then
			--verify wich supplier is cheapeast and add to suggested order
			if @stock < (select MIN_QTY from INGREDIENTS where ID=@ingredientID)
				begin
				declare @supplierID int
				set @supplierID=0
				select @supplierID=temp.ID from
					(select TOP 1 SUPPLIER_ID as ID, AVG(PRICE) as av
						from LOT where INGREDIENTS_ID=@ingredientID
						group by SUPPLIER_ID
						order by 2) as temp
				insert into @suggestionTemp values (@ingredientID, @supplierID, 
					(select ORDER_QTY from INGREDIENTS where ID=@ingredientID))
				end			
			fetch next from ingredients into @ingredientID, @reserved
			end
		close ingredients
		deallocate ingredients
	return
	end
	
	





