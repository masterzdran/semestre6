USE SI2_AP1;
set dateformat dmy;

/*I - b)*/
/*procedimento que recebe o identificador e gera uma leitura*/

drop procedure geraLeitura
create procedure geraLeitura(@sensor char(9)) as
	begin transaction
	insert into dbo.Leitura(sensorName, valor, instanteLeitura) values(@sensor, 20 * rand(), SYSDATETIME())
	commit
	
drop trigger alarmeLeitura
create trigger alarmeLeitura
	on Leitura
	after INSERT
	as
		declare @valor decimal(10), @sensor char(9), @inf decimal(10), @sup decimal(10), @instante datetime
		select @valor = valor, @sensor = sensorName, @instante=instanteLeitura from INSERTED
		select @inf = limitInf, @sup = limitSup from Sensor 
			where (Sensor.name = @sensor)
		
		begin
		if( @valor > @sup OR @valor < @inf)
		insert into dbo.Alarme(
			sensorName, 
			sensorLimInf, 
			sensorLimSup,
			leituraValor,
			instanteLeitura)
		values(@sensor,
			   @inf,
			   @sup,
			   @valor,
			   @instante)		
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