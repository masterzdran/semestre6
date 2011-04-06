drop table alunos;
create Table alunos (
   numero decimal(9) primary key,
   nome varchar(50),
)
go
insert into alunos values(1111,'Jorge Silva')
insert into alunos values(2222,'Ana Rita')
go
drop table alunos_ts;
create Table alunos_ts (
   numero decimal(9) primary key,
   nome varchar(50),
   ts timestamp
)
go

insert into alunos_ts(numero,nome) values(1111,'Jorge Silva')
insert into alunos_ts(numero,nome) values(2222,'Ana Rita')
go

drop proc p;
go
create proc p @p1 int, @p2 int output
-- parâmetro de output, valor de retorno e result set
as
   set @p2 = @p1+@p1
   SELECT * from Alunos
   return @p1+@p2

Go

drop table regioesADO;
create Table regioesADO (
  reg varchar(10) primary key,
  descr varchar(50)
)

GO

drop table vendasADO;
create Table vendasADO (
  produto varchar(10) primary key,
  quantidade int,
  custoUnitario real,
  regiao varchar(10) not null foreign key references regioesADO
)

GO
insert into regioesADO values('reg1', 'primeira regiao')
insert into regioesADO values('reg2', 'segunda regiao')

insert into vendasADO values('prod2', 10, 10.1, 'reg1')
insert into vendasADO values('prod3', 100, 0.7, 'reg2')
insert into vendasADO values('prod4', 15, 21.7, 'reg2')
insert into vendasADO values('prod5', 122, 10.0, 'reg2')

GO

drop table disciplinas;
create Table disciplinas (
  cod varchar(5) primary  key,
  nome varchar(50),
  ts timestamp
)



Go

insert into disciplinas (cod, nome) values('lc', 'Logica e Computacao')
insert into disciplinas (cod, nome) values('isi', 'introducao aos sistemas de informacao')
insert into disciplinas (cod, nome) values('si', 'sistemas de informacao')
insert into disciplinas (cod, nome) values('mads', 'metodologias de an. e des. de sistemas')
insert into disciplinas (cod, nome) values('rec', 'representacao e exploracao de conhecimento')
insert into disciplinas (cod, nome) values('sint', 'sistemas inteligentes')

Go

select * from disciplinas
Go

drop proc sp1
GO
CREATE PROC sp1 AS
  print 'mensagem 1'
  raiserror ('Erro 1',10,1)
  print 'mensagem 2'
  select * from alunos
GO
drop proc actualizaralunos;
GO
CREATE PROC ActualizarAlunos (
	@numNovo int, @nomeNovo varchar(10), @numOrig int, @tsOrig timestamp,
	@tsNovo timestamp output)
AS
	UPDATE alunos_ts
	SET numero = @numNovo, nome = @nomeNovo
	WHERE numero = @numOrig AND ts = @tsOrig
	if @@ROWCOUNT = 1
	SELECT @tsNovo = ts
	FROM alunos_ts WHERE numero = @numNovo


select * from alunos_ts
insert into alunos_ts(numero,nome) values(200,'bla2')

SELECT numero, nome FROM Alunos_ts
delete alunos_ts where numero = 2222