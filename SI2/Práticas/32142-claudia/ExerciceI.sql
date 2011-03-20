use Aula_Pratica1_SI2;
--Exercice I b)
set dateformat dmy;
if OBJECT_ID('insertLeitura') IS NOT NULL
	drop procedure insertLeitura;
go
create procedure insertLeitura(
	@NomeSensor char(9), @Valor decimal(10))

as
	insert into leitura values(@Valor,GETDATE(),@NomeSensor);
go
declare @n char(9), @v decimal(10)
set @n = 'SENSOR002' set @v = 15;

exec insertLeitura @n, @v


--Exercice I c)
select * from sensor;
select * from leitura;
select * from alarme;