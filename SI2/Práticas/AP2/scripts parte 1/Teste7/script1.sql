-- ********** Teste 7 **********
--tempo t0:
use db_si_ap
GO
ALTER DATABASE db_si_ap
    SET ALLOW_SNAPSHOT_ISOLATION OFF
ALTER DATABASE db_si_ap
    SET READ_COMMITTED_SNAPSHOT OFF
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
