--Este código assume a existência da BD
-- db_si_ap.
--No ambiente de laboratório, esta BD está associada ao utilizador si_ap
if object_id('db_si_ap') is null
	create database db_si_ap;


GO

use db_si_ap;
ALTER DATABASE db_si_ap
	SET READ_COMMITTED_SNAPSHOT OFF;
ALTER DATABASE db_si_ap
	SET ALLOW_SNAPSHOT_ISOLATION OFF;
GO

if object_id('conta') is not null
	drop table conta;

create table conta
(
   id integer primary key,
   saldo real not null
);

insert into conta values(1,1000);
insert into conta values(2,2000);