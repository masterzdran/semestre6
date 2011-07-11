use SI2_TP1;

if OBJECT_ID('competences_view') IS NOT NULL
	drop view competences_view;
go	
create view competences_view as
select RESTAURANTS.ID as restaurantid , RESTAURANTS.NAME as restaurantname, 
	   EMPLOYEE_PROFICIENCY.PROFICIENCY_ID as competenceid, PERSON.NAME as employeename, PROFICIENCY.NAME as competencename
	   from EMPLOYEE inner join RESTAURANTS on EMPLOYEE.RESTAUNRANT_ID = RESTAURANTS.ID
				     inner join EMPLOYEE_PROFICIENCY on EMPLOYEE_PROFICIENCY.EMPLOYEE_ID = EMPLOYEE.PERSON_ID
				     inner join PROFICIENCY on PROFICIENCY.ID = EMPLOYEE_PROFICIENCY.PROFICIENCY_ID
				     inner join PERSON on PERSON.ID = EMPLOYEE.PERSON_ID;
