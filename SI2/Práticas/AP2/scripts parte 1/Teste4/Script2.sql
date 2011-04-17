-- ************* Teste 4 ************
--tempo t2:
use db_si_ap
begin transaction

--tempo t4
update conta set saldo = saldo+100 where id = 1
commit

--select * from conta
--update conta set saldo = saldo-100 where id = 1