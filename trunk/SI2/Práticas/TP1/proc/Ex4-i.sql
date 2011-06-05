use SI2_TP1
/*Ex4 - i)
	Listar os nomes dos clientes que moram em ‘Lisboa’ e no ‘Porto’.
*/
if OBJECT_ID('SelectClientOnSpecifyCity') IS NOT NULL
	drop function SelectClientOnSpecifyCity;
go
create function SelectClientOnSpecifyCity(@city char(50))
returns @suggestionTemp_C table(
			NAME			varchar(30),
			CITY			char(50),
			CONTACT			char(20))
as
	begin
		
		insert into @suggestionTemp_C select CUSTOMER.NAME, ADDRESS.CITY, CUSTOMER.CONTACT
							from REGISTERED inner join CUSTOMER on REGISTERED.CUSTOMER_ID = CUSTOMER.ID
							 inner join ADDRESS on REGISTERED.ADDRESS_ID = ADDRESS.ID
							where ADDRESS.CITY = @city
return			
end
