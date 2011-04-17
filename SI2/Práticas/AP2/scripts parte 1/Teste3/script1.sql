-- ********** Teste 3 **********
--tempo t1:
use db_si_ap
set transaction isolation level read uncommitted
/* uma transacção de 1º grau nao exibe as anomalias 
“overwriting uncommited data” */
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
/*
transaction read uncommitted - Dirty Read: a session can read rows changed
by transactions in other sessions that have not been committed. If the other
session then rolls back its transaction, subsequent reads of the same
rows will find column values returned to previous values, deleted rows
reappearing and rows inserted by the other transaction missing.

In this case, the value of id=2 it was change with transaction repeatable read
the current transaction have to wait that other transaction close
*/

--tempo t7
rollback 

