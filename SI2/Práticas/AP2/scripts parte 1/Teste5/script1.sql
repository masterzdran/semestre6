-- ********** Teste 5 **********
--tempo t0
if object_id('#temp') is not null
	drop table #temp
create table #temp 
(
	id int, saldo real
)

use db_si_ap
delete from conta
--repor os valores inicias em conta
insert into conta values(1,1000)
insert into conta values(2,2000)

--tempo t1:
set transaction isolation level read committed
begin transaction

--tempo t3
declare @s1 real
select @s1 = saldo from conta where id = 1;
insert into #temp values(1,@s1);
print @s1

-- tempo t5
declare @s2 real
select @s2 = saldo from #temp where id = 1
set @s2 = @s2+3000
update conta set saldo = @s2 where id = 1
commit
declare @s3 real
select @s3 = saldo from conta where id = 1
print @s3
