use Aula_Pratica1_SI2;

create table sensor(
	Name char(9),
	Valor_Inferior decimal(10),
	Valor_Superior decimal(10),
	primary key (Name)
);

create table leitura(
	id int identity(1,1),
	Valor decimal(10),
	InstanteLeitura datetime,
	NomeSensor char(9),
	primary key(id),
	foreign key(NomeSensor) references sensor(Name)
)

create table alarme(
	Instanteleitura datetime,
	Sensor_Val_Inf decimal(10),
	Sensor_Val_Sup decimal(10),
	ID_Sensor char(9),
	tipo binary(1),
	ValorExpectavel decimal(10),
	primary key(Instanteleitura)
)