@echo off
set server=localhost\SQLEXPRESS
set db=SI2_TP1

ECHO Processing scripts... %TIME%  >output.txt
REM sqlcmd.exe  -S localhost\SQLEXPRESS -E   -d SI2_TP1 -i run_all.sql >>output.txt

ECHO Droping tables... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\1-droptables_tp1.sql >>output.txt
ECHO Done! >>output.txt
ECHO Creating tables... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\2-create_tables_tp1.sql >>output.txt
ECHO Done! >>output.txt
ECHO Creating triggers... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\trigger1.sql >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\trigger2.sql >>output.txt
ECHO Done! >>output.txt
ECHO Creating Procedures... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\Ex4-a.sql >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\Ex4-b.sql >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\Ex4-c.sql >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\Ex4-d.sql >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\Ex4-e.sql >>output.txt


ECHO Data feed... >>output.txt
REM sqlcmd.exe  -S %server% -E -d %db% -i %CD%\3-data_feed_tp1.sql >>output.txt
ECHO Done! >>output.txt

ECHO Done processing! >>output.txt

type output.txt | more
