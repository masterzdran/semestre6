@echo off
set server=localhost\SQLEXPRESS
set db=SI2_TP1
set dbmaster=master
ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Processing scripts... %TIME%  >output.txt
REM sqlcmd.exe  -S localhost\SQLEXPRESS -E   -d SI2_TP1 -i run_all.sql >>output.txt

ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Droping tables and data base SI2_TP1... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\1-droptables_tp1.sql >>output.txt
ECHO Done! >>output.txt

ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Creating data base SI2_TP1... >>output.txt
sqlcmd.exe  -S %server% -E -d %dbmaster% -i %CD%\2-createdb-si2-tp1.sql >> output.txt
ECHO Done! >>output.txt

ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Creating tables... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\3-create_tables_tp1.sql >>output.txt
ECHO Done! >>output.txt
ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Creating triggers... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\trigger1.sql >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\trigger2.sql >>output.txt
ECHO Done! >>output.txt

ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Creating Procedures... >>output.txt
ECHO a)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\CreateCourses.sql >>output.txt
ECHO b)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\CreateEvent.sql >>output.txt
ECHO c)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\TakeIndividualReservation.sql >>output.txt
ECHO d)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\EventCost.sql >>output.txt
ECHO e)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\CaptivateIngredients.sql >>output.txt
ECHO f)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\SuggestOrder.sql >>output.txt
ECHO g)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\UpdateStockWithSupplier.sql >>output.txt
ECHO h)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\OutOfValidity.sql >>output.txt
ECHO i)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\SelectClientOnSpecifyCity.sql >>output.txt
ECHO j)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\MostSaleCourses.sql >>output.txt
ECHO k)... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\MostProfitMenu.sql >>output.txt

ECHO ---------------------------------------------------------------------------- >>output.txt
ECHO Data feed... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\4-data_feed_tp1.sql >>output.txt
ECHO Data feed... >>output.txt
sqlcmd.exe  -S %server% -E -d %db% -i %CD%\XMLCompetenceView.sql >>output.txt
ECHO Done! >>output.txt

ECHO Done processing! >>output.txt

ECHO ---------------------------------------------------------------------------- >>output.txt
type output.txt | more
