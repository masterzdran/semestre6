-- ********** Teste 9 **********
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

--tempo t1:
set transaction isolation level snapshot
begin transaction

--tempo t2
declare @m real
select @m = avg(saldo) from conta where saldo > 500
print @m

--tempo t4
declare @m1 real
select @m1 = avg(saldo) from conta where saldo > 500
print @m1

--tempo t6
declare @m2 real
select @m2 = avg(saldo) from conta where saldo > 500
print @m2
commit

--tempo t7
declare @m3 real
select @m3 = avg(saldo) from conta where saldo > 500
print @m3
