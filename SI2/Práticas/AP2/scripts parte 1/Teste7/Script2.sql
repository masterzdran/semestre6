-- ************* Teste 7 ************
--tempo t3
use db_si_ap
begin tran
update conta set saldo = saldo+1000 where id = 1

--tempo t6
update conta set saldo = saldo+10000 where id = 1
update conta set saldo = saldo-100 where id = 2

--tempo t9
commit