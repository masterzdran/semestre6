-- ********** Teste 7 **********

--tempo t4
use db_si_ap
print 'ID da BD db_si_ap:' + cast(db_id('db_si_ap') as varchar(5))
SELECT * FROM sys.dm_tran_version_store;

--tempo t8
SELECT * FROM sys.dm_tran_version_store;

--tempo t10
SELECT * FROM sys.dm_tran_version_store;
GO
waitfor delay '00:01:10' --Esperar que as versões sejam removidas
SELECT * FROM sys.dm_tran_version_store;

