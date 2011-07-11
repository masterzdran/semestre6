use SI2_TP1
/*Ex4 - g)
	Actualizar o stock do armazém com a aquisição a um determinado fornecedor.
*/
if OBJECT_ID('UpdateStockWithSupplier') IS NOT NULL
	drop procedure UpdateStockWithSupplier;
go
create procedure UpdateStockWithSupplier(@idEncomenda int, @invoice int, @quantityreceive int,
										@validity datetime, @price smallmoney, @orderQuantityLeft bit, @dateExpectedOfNewOrder datetime)
as
	begin transaction
	
	declare @idsupplier int, @idingredient int, @qty_ordered int,
			@dateorder datetime, @dateexpectedorder datetime, @idlot int
	
	select @idsupplier=ORDERS.SUPPLIER_ID, @idingredient = ORDERS.INGREDIENT_ID,
				@qty_ordered = ORDERS.QTY_ORDERED, @dateorder = ORDERS.DATE,
				@dateexpectedorder = ORDERS.EXPECTED_DATE from ORDERS
	
	--insert in lot the order because we alredy pay it
	insert into LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
		values(@idingredient, @idsupplier, @invoice, GETDATE(), @quantityreceive ,@price,
				@validity, @quantityreceive);
				
	select @idlot = LOT.ID from LOT
			where LOT.INGREDIENTS_ID = @idingredient AND LOT.SUPPLIER_ID = @idsupplier AND
				LOT.INVOICE = @invoice AND LOT.VALIDITY = @validity AND LOT.QTY = @quantityreceive
				AND LOT.PRICE = @price
				
	--insert this buy in history order
	insert into ORDERS_LOG(SUPPLIER_ID, INGREDIENTS_ID, DATE, QTY_ORDERED, EXPECTED_DATE, LOT_ID)
		values(@idsupplier, @idingredient, @dateorder, @qty_ordered - @quantityreceive, @dateexpectedorder,
							@idlot);
		
	--if bit of @orderQuantityLeft is 1 that means that we should order the rest of quantity
	if @orderQuantityLeft = 1
	begin
		if @quantityreceive < @qty_ordered
		begin
			insert into ORDERS (SUPPLIER_ID, INGREDIENT_ID, DATE, QTY_ORDERED, EXPECTED_DATE)
				values(@idsupplier, @idingredient, GETDATE(), (@qty_ordered - @quantityreceive), @dateExpectedOfNewOrder);
		end
	end
	
	--remove of table order this order that its already 
	delete from ORDERS where ORDERS.ID = @idEncomenda
	commit