USE SI2_AP1;
set dateformat dmy;

insert into dbo.Sensor(name, limitInf, limitSup) values('SENSOR001',8,16)
insert into dbo.Sensor(name, limitInf, limitSup) values('SENSOR002',10,12)
insert into dbo.Sensor(name, limitInf, limitSup) values('SENSOR003',2,18)
GO


declare @i int
set @i = 0

while @i <10
begin
	exec geraLeitura 'SENSOR001'
	exec geraLeitura 'SENSOR002'
	exec geraLeitura 'SENSOR003'
	set @i = @i+1	
end

select * from Sensor
select * from Leitura
select * from Alarme

/*I- c)*/
SELECT @@TOTAL_READ AS 'Reads', GETDATE() AS 'As of'
--relatório de escrita 
SELECT @@TOTAL_WRITE AS 'Writes', GETDATE() AS 'As of'