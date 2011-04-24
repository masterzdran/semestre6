-- ********** Teste 7 **********
--tempo t0:
use db_si_ap
GO
ALTER DATABASE db_si_ap
    SET ALLOW_SNAPSHOT_ISOLATION OFF
/*
the instance of the Microsoft SQL Server Database
Engine does generate row versions for
modified data until all active transactions
that have modified data in the database complete
*/
ALTER DATABASE db_si_ap
    SET READ_COMMITTED_SNAPSHOT OFF
/* when READ_COMMITTED_SNAPSHOT is on:
only the connection executing the ALTER DATABASE command is allowed in the database
when is off, it means that alter database is possible from any transaction
*/
GO
set transaction isolation level read committed
begin tran
delete from conta
insert into conta values(1,1000)
insert into conta values(2,2000)
commit
GO
ALTER DATABASE db_si_ap
    SET ALLOW_SNAPSHOT_ISOLATION ON
GO
--tempo t1:
set transaction isolation level snapshot
begin transaction

--tempo t2
declare @s1 real
select @s1 = saldo from conta where id = 1
print @s1

--tempo t5
declare @s2 real
select @s2 = saldo from conta where id = 1
print @s2

--tempo t11
declare @s2 real
select @s2 = saldo from conta where id = 1
print @s2
commit

--tempo t12
declare @s2 real
select @s2 = saldo from conta where id = 1
print @s2
