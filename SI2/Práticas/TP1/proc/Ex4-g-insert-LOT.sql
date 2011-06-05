use SI2_TP1
/*Ex4 - g)
	Actualizar o stock do armazém com a aquisição a um determinado fornecedor.
*/
if OBJECT_ID('UpdateStockWithSupplier') IS NOT NULL
	drop procedure UpdateStockWithSupplier_2;
go
create procedure UpdateStockWithSupplier_2(@ID_Supplier int, @ID_Ingredient int, @totalprice smallmoney)
as
	begin transaction
	
	declare @date datetime, @qty_ordered int, @expected_date datetime
	
	select * 
	
	--ORDERS(ID[PK],SUPPLIER_ID[FK], INGREDIENT_ID[FK], DATE, QTY_ORDERED, EXPECTED_DATE)
	
	commit
go
