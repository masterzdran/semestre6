-- ********** Teste 4 **********
--tempo t1:
use db_si_ap
set transaction isolation level read committed
begin transaction

--tempo t3
declare @s1 real
select @s1 = saldo from conta where id = 1
print @s1

-- tempo t5
declare @s2 real
select @s2 = saldo from conta where id = 1
print @s2
rollback

