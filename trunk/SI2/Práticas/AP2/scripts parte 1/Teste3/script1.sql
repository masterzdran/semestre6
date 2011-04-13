-- ********** Teste 3 **********
--tempo t1:
use db_si_ap
set transaction isolation level read uncommitted
begin transaction

--tempo t3
declare @saldo real
select @saldo=saldo from conta where id = 1
print @saldo
set @saldo=@saldo+100
update conta set saldo = @saldo where id = 1
print @saldo

-- tempo t5
declare @saldo real
select @saldo=saldo from conta where id = 2
print @saldo
set @saldo=@saldo+100
update conta set saldo = @saldo where id = 2
print @saldo

--tempo t7
rollback 

