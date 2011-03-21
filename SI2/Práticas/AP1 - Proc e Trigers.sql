USE SI2_AP1;
set dateformat dmy;

/*I - b)*/
/*procedimento que recebe o identificador e gera uma leitura*/
IF EXISTS(SELECT * FROM sys.objects WHERE type = 'P' AND name = 'geraLeitura')
	DROP PROCEDURE geraLeitura
go

create procedure geraLeitura(@sensor char(9))
as
	begin transaction
	insert into dbo.Leitura(sensorName, valor, instanteLeitura) values(@sensor, 20 * rand(), SYSDATETIME())
	commit
	
go

/*II-b)*/
IF EXISTS(SELECT * FROM sys.objects WHERE type = 'P' AND name = 'geraAlarme')
	DROP PROCEDURE geraAlarme
go

create procedure geraAlarme(@sensorName char(9), @sensorLimInf decimal, @sensorLimSup decimal,
									@leituraValor decimal(10))
as
	begin transaction
	declare @tipo char(3)
	set @tipo = ''
	if(@leituraValor > @sensorLimSup)
	begin
		set @tipo = 'max'
	end
	if(@leituraValor < @sensorLimInf)
	begin
		set @tipo = 'min'
	end	
	if (@tipo != '')
	begin
		insert into dbo.Alarme values(@sensorName, @sensorLimInf, @sensorLimSup, @leituraValor, SYSDATETIME(), @tipo)
	end
commit
go

/*II-c)*/
IF EXISTS(SELECT * FROM sys.objects WHERE type = 'TR' AND name = 'alarmeLeitura')
	DROP TRIGGER alarmeLeitura
go

create trigger alarmeLeitura
	on Leitura
	after INSERT
	as
	declare @valor decimal(10), @sensor char(9), @inf decimal(10), @sup decimal(10), @instante datetime, @tipo char(3)
	set @tipo = ''
	select @valor = valor, @sensor = sensorName, @instante=instanteLeitura from INSERTED
	select @inf = limitInf, @sup = limitSup from Sensor 
			where (Sensor.name = @sensor)
		begin
		if(@valor > @sup)
		begin
			set @tipo = 'max'
		end
		if(@valor < @inf)
		begin
			set @tipo = 'min'
		end	
		if (@tipo != '')
		begin
			insert into dbo.Alarme values(@sensor, @inf, @sup, @valor, @instante, @tipo)
		end
	end

/*
create view alarme_tipo(id_alarm, nome, inf, sup, valor, dataHora, tipo)
	as
		select (id, sensorName, sensorLimInf, sensorLimSup, leituraValor, instanteLeitura
			(select case
				when valor>sup then 'max'
				else 'min'
			 end
			)
		) from Alarme
		*/