use SI2_TP1
/*Ex4 - i)
	Listar os nomes dos clientes que moram em ‘Lisboa’ e no ‘Porto’.
*/
if OBJECT_ID('ListClientsInPortoAndLisbon') IS NOT NULL
	drop procedure ListClientsInPortoAndLisbon;
go
create procedure ListClientsInPortoAndLisbon
as
	begin transaction
		select * from REGISTERED where 
			(REGISTERED.ADDRESS_ID.CITY = 'Lisboa' AND
				REGISTERED.ADDRESS_ID.CITY = 'Porto')
	commit
go
