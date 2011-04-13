-- ********** Teste 7 **********
--tempo t7:
use db_si_ap
set transaction isolation level read committed
begin tran

declare @s1 real
select @s1 = saldo from conta where id = 1
print @s1

commit