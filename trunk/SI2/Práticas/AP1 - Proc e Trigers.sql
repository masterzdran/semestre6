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
		begin
		insert into dbo.Alarme(
			sensorName, 
			sensorLimInf, 
			sensorLimSup,
			leituraValor,
			instanteLeitura)
		select novo.sensorName, Sensor.limitInf, Sensor.limitSup, novo.valor, novo.instanteLeitura
			from INSERTED as novo INNER JOIN Sensor
				on novo.sensorName = Sensor.name
				where (novo.valor>Sensor.limitSup OR novo.valor<Sensor.limitInf)
		end
