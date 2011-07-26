use SI2_TP1;
/*Ex4 - j)
	Listar as porções individuais mais vendidas agrupados por tipo (entrada, prato, sobremesa, …)
*/
if OBJECT_ID('PurchaseAnalysis') IS NOT NULL
	drop function PurchaseAnalysis;
go	

create function PurchaseAnalysis(@start_time datetime, @end_time datetime, @deviance decimal)
returns @Analysis table(
			ID_ING			int,
			ING_NAME		char(30),
			ID_SUPP			int,
			SUP_NAME		char(30),
			INVOICE			int,
			DATE			datetime,
			QTY				decimal(10,3),
			PRICE			smallmoney,
			AVERAGE_PRICE	smallmoney)
as
	begin
		declare @ing_id int, @sup_id int, @invoice int, @date datetime, @qty int, @price smallmoney
		declare @ing_name char(30), @sup_name char(30), @average_price smallmoney, @_price smallmoney
		--get all purchases between start and end date to start analysis
		declare temp cursor
		for select INGREDIENTS.ID, SUPPLIERS.ID, LOT.INVOICE, LOT.DATE, LOT.QTY, LOT.PRICE
		from LOT, INGREDIENTS, SUPPLIERS where DATE > @start_time AND DATE < @end_time AND LOT.[INGREDIENTS_ID] = INGREDIENTS.ID
				AND LOT.[SUPPLIER_ID] = SUPPLIERS.ID
		
		open temp
		fetch next from temp into @ing_id, @sup_id, @invoice, @date, @qty, @price
		while(@@FETCH_STATUS=0)
			begin
			select @average_price = AVG(LOT.PRICE) from LOT where LOT.[INGREDIENTS_ID]=@ing_id
			set @_price = @average_price + @average_price * @deviance
			--check if deviance from price is bigger than deviance received
			--if deviance bigger inser into table Analysis to return
			if @price > @_price
				begin
				select @ing_name = INGREDIENTS.NAME from INGREDIENTS
					where INGREDIENTS.ID = @ing_id
				select @sup_name = SUPPLIERS.NAME from SUPPLIERS
					where SUPPLIERS.ID = @sup_id
				insert into @Analysis values(@ing_id, @ing_name, @sup_id, @sup_name, @invoice,
												@date, @qty, @price, @average_price)
				end
			fetch next from temp into @ing_id, @sup_id, @invoice, @date, @qty, @price
		end
		close temp
		deallocate temp
	return
	end
