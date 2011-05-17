use db_si_ap;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'compras')
drop table compras;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'encomenda')
drop table encomenda;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'fornecedores')
drop table fornecedores;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'p_i')
drop table p_i;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'ingredientes')
drop table ingredientes;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'car_p')
drop table car_p;	

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'pratos')
drop table pratos;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'reservaevento')
drop table reservaevento;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'amigos')
drop table amigos;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'cli_r')
drop table cli_r;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'reservanormal')
drop table reservanormal;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'cardapio')
drop table cardapio;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'clienteregistado')
drop table clienteregistado;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'reuniao')
drop table reuniao;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'comentario')
drop table comentario;

if exists(select * 
		from INFORMATION_SCHEMA.TABLES
		where TABLE_NAME = 'cliente')
drop table cliente;