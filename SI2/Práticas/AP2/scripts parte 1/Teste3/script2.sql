
-- ************* Teste 3 ************
--tempo t2:
use db_si_ap
set transaction isolation level repeatable read
/* uma transacção de 3ª grau não exibe as anomalias 
“overwriting uncommited data” e “non repeatable reads” 
(consequentemente, não exibe a anomalia “dirty reads”) */
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
/*
The current transaction can't read "saldo" of id=1, because "saldo" it wasn't commited.
An error is lanch because there is deadlock about this transaction, so this one is close by SGBD.
*/
--tempo t8
rollback
