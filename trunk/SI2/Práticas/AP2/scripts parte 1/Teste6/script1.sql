-- ********** Teste 6 **********
--tempo t0:
use db_si_ap
delete from conta
insert into conta values(1,1000)
insert into conta values(2,2000)

--tempo t1:
set transaction isolation level  repeatable read
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

select * from conta
