
-- ************* Teste 2 ************
-- tempo t2
use db_si_ap
begin transaction

-- tempo t3
declare @saldo real
select @saldo=saldo from conta where id = 2
print @saldo
update conta set @saldo=saldo = @saldo-500 where id = 2
print @saldo

--tempo t6
rollback