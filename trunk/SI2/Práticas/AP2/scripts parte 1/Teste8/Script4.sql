-- ********** Teste 8 **********
--tempo t4
use db_si_ap
select 'ID da BD db_si_ap:' + cast(db_id('db_si_ap') as varchar(5))
SELECT * FROM sys.dm_tran_version_store;

--tempo t8
SELECT * FROM sys.dm_tran_version_store;

--tempo t10
SELECT * FROM sys.dm_tran_version_store;
GO
waitfor delay '00:01:10' --Execute os tempos T11 e T12 e depois volte aqui para ver o resultado
SELECT * FROM sys.dm_tran_version_store;

