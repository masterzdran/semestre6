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
		insert into @suggestionTemp_C select PERSON.NAME, ADDRESS.CITY, PERSON.CONTACT
							from REGISTERED inner join CUSTOMER on REGISTERED.CUSTOMER_ID = CUSTOMER.PERSON_ID
							inner join ADDRESS on REGISTERED.ADDRESS_ID = ADDRESS.ID inner join PERSON on CUSTOMER.PERSON_ID = PERSON.ID
							where ADDRESS.CITY = @city
return			
end
