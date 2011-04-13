
-- ************* Teste 3 ************
--tempo t2:
use db_si_ap
set transaction isolation level repeatable read
begin transaction

--tempo t4
declare @saldo real
select @saldo=saldo from conta where id = 2
print @saldo
set @saldo=@saldo+100
update conta set saldo = @saldo where id = 2
print @saldo

--tempo t6
declare @saldo real
select @saldo=saldo from conta where id = 1
print @saldo
set @saldo=@saldo+100
update conta set saldo = @saldo where id = 1
print @saldo

--tempo t8
rollback