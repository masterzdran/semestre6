use SI2_TP1
/*Ex4 - g)
	Actualizar o stock do armazém com a aquisição a um determinado fornecedor.
*/
if OBJECT_ID('UpdateStockWithSupplier') IS NOT NULL
	drop procedure UpdateStockWithSupplier;
go
create procedure UpdateStockWithSupplier(@ID_Supplier int, @ID_Ingredient int, @expectedDate datetime)
as
	begin transaction
	
	declare @current decimal(10,3), @reserved decimal(10,3), @min decimal(10,3), @max decimal(10,3)
	
	select @reserved = QTY_RESERVED, @current = QTY_CURRENT, @min = MIN_QTY, @max = ORDER_QTY
			from INGREDIENTS where ID = @ID_Ingredient
	set @current = @current + @reserved
	
	--if quantity is lower than minimum number of order
	--we request to supplier the minimum
	if @current < @min
	begin
		declare @dif1 decimal(10,3)
		set @dif1 = @min - @current
		set @current = @current + @dif1
	end
	else --if quantity is higher then number of order, we reduce this one
	begin
		declare @dif2 decimal(10,3)
		set @dif2 = @current - @max
		set @current = @current + @dif2
	end
	
	--insert information about an order
	insert into ORDERS (SUPPLIER_ID, INGREDIENT_ID, DATE, QTY_ORDERED, EXPECTED_DATE)
						values(@ID_Supplier, @ID_Ingredient, GETDATE(), @current, @expectedDate);
	
	--know what is reserved quantity that remains after order
	set @reserved = @reserved - @current
	if @reserved < 0
		set @reserved = 0
	
	--update table INGREDIENTS
	update INGREDIENTS set QTY_RESERVED = @reserved from INGREDIENTS where ID = @ID_Ingredient
	
	commit
go
