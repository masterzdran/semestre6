/*
Modelo Relacional:

livro(isbn [pk], nome)
capitulo(numero [pk] ,isbn [pk], nome )
critico(id [pk], nome)
critica_livro(id [pk] ,isbn [k],	conteudo , pontuacao )
*/
use db_si_ap
if object_id('Critica_livro') is not null
	drop table Critica_livro

if object_id('Capitulo') is not null
	drop table Capitulo


if object_id('livro') is not null
	drop table livro
	
if object_id('Critico') is not null
	drop table Critico

go

	
create table Livro
(
	isbn varchar(13) primary key,
	nome varchar(20) not null
)

create table Critico
(
	[id] int primary key,
	nome varchar(20) not null	
)

create table Critica_livro
(
	[id] int not null references critico([id]),
	isbn varchar(13) not null references livro(isbn),
	conteudo varchar(1024) not null,
	pontuacao int not null,
	check (pontuacao >= 0 AND pontuacao <6),
	primary key(id,isbn)
)

create table capitulo
(
	numero int not null,
	isbn varchar(13) not null references livro(isbn),
	nome varchar(20) not null,
	primary key (numero,isbn) 
	
)

insert into Critico values (1, 'Jose Ma Lingua')
insert into Critico values (2, 'Homem Viperino de Sa')
insert into Critico values (3, 'Josefa Pureza')

insert into Livro values (1234567890, 'Livro Curto')
insert into Livro values (1234567891, 'Livro Medio')
insert into Livro values (1234567892, 'Livro Longo')

insert into Capitulo values (1,1234567890, 'Cap. 1')
insert into Capitulo values (1,1234567891, 'Cap. 1')
insert into Capitulo values (2,1234567891, 'Cap. 2')
insert into Capitulo values (1,1234567892, 'Cap. 1')
insert into Capitulo values (2,1234567892, 'Cap. 2')
insert into Capitulo values (3,1234567892, 'Cap. 3')

insert into Critica_livro values (1,1234567890,'Grande seca',1)
insert into Critica_livro values (2,1234567890,'O melhor para limpar os vidros',1)
insert into Critica_livro values (3,1234567890,'Melhor, só o último da Carolina',2)

insert into Critica_livro values (1,1234567891,'Recomendado',4)
insert into Critica_livro values (2,1234567891,'Com conta, peso e medida',5)

insert into Critica_livro values (3,1234567892,'Obra (quase) prima',4)
