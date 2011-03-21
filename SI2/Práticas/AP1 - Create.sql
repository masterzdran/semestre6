
IF db_id('SI2_AP1') is null
	CREATE DATABASE AP1;
GO

USE SI2_AP1;
set dateformat dmy;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'Leitura')
drop table dbo.Leitura;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'Sensor')
drop table dbo.Sensor;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'Alarme')
drop table dbo.Alarme;

create table Sensor(
	name char(9) not null,
	limitInf decimal(10) not null,
	limitSup decimal(10) not null,
	constraint pk_Sensor primary key (name)
)

create table Leitura(
	id int identity(1,1),
	sensorName char(9) not null,
	valor decimal(10) not null,
	instanteLeitura datetime not null,
	constraint pk_Leitura primary key(id),
	constraint fk_Leitura foreign key(sensorName) references Sensor(name)
)

create table Alarme(
	id int identity(1,1),
	sensorName char(9) not null,
	sensorLimInf decimal not null,
	sensorLimSup decimal not null,
	leituraValor decimal(10) not null,
	instanteLeitura datetime not null,
	tipo char(3) not null,
	constraint pk_Alarme primary key(id),
	constraint ck_Alarme_Tipo check(tipo='min' or tipo='max')
)