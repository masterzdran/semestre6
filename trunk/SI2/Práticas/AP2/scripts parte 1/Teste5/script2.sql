
-- ************* Teste 5 ************
--tempo t2:
use db_si_ap
begin transaction

--tempo t4
update conta set saldo = saldo+5000 where id = 1
commit
select saldo from conta where id = 1