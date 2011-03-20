use Aula_Pratica1_SI2;

--Exercice II
IF OBJECT_ID ('InsertAlarme') IS NOT NULL
   DROP TRIGGER InsertAlarme
GO
CREATE TRIGGER InsertAlarme
ON leitura
FOR INSERT
AS
   declare @val decimal(10), @nome char(9), @inst datetime, @ValInf decimal(10), @ValSup decimal(10)
   select @val = Valor, @nome = NomeSensor, @inst = InstanteLeitura
		from INSERTED
   print @nome
   
   select @ValInf = Valor_Inferior, @ValSup = Valor_Superior from sensor as s
			where s.Name like @nome;
   
   if @val < @ValInf
   BEGIN
	insert into alarme values(@inst,@ValInf,@ValSup, @nome,0,@val);
   END
   if @val > @ValSup
   BEGIN
	insert into alarme values(@inst,@ValInf,@ValSup, @nome,1,@val);
   END
GO
