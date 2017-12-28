SET LINESIZE 160
SET SERVEROUTPUT ON
1.
alter session set NLS_DATE_FORMAT = 'dd.mm.yyyy HH24:mi:ss';
SELECT * FROM Н_СЕССИЯ;
2.
SELECT DISTINCT НАИМЕНОВАНИЕ FROM Н_ДИСЦИПЛИНЫ;
3.
#select ДАТА_РОЖДЕНИЯ from Н_ЛЮДИ where rownum <= 1
#select DATEDIFF(day, '2017-08-01 00:00:00', '2017-09-01 00:00:00')
#SELECT TO_DATE('05.07.2007 09:53:01')-TO_DATE('05.08.2007 09:53:01') FROM Н_ЛЮДИ;
#SELECT TO_DATE('05.07.2007 09:53:01')-TO_DATE('05.08.2007 09:53:01') AS DIFF FROM Н_ЛЮДИ where rownum<=1;
#SELECT TO_DATE('01.09.2017 00:00:00')-(select ДАТА_РОЖДЕНИЯ from Н_ЛЮДИ where rownum <= 1) AS DIFF FROM Н_ЛЮДИ where rownum<=1;
SELECT TO_DATE('01.09.2017 00:00:00')-(select * from (select ДАТА_РОЖДЕНИЯ from Н_ЛЮДИ order by dbms_random.value) where rownum <= 1) AS DIFF FROM Н_ЛЮДИ where rownum<=1;
4.
select ФАМИЛИЯ||' '||SUBSTR(ИМЯ,1,1)||'.'||SUBSTR(ОТЧЕСТВО,1,1)||'.' ФАМИЛИЯ_И_ИНИЦИАЛЫ from Н_ЛЮДИ 
where EXTRACT(month from ДАТА_РОЖДЕНИЯ) = (select * from (select EXTRACT(month from ДАТА_РОЖДЕНИЯ) МЕСЯЦ from Н_ЛЮДИ order by dbms_random.value) where rownum<=1);
5.
SELECT SUBSTR((select * from (select ФАМИЛИЯ from Н_ЛЮДИ order by dbms_random.value) where rownum<=1),1,2)||'%' FROM Н_ЛЮДИ;
select ФАМИЛИЯ||' '||ИМЯ||' '||ОТЧЕСТВО ФИО, ИД FROM Н_ЛЮДИ 
where ФАМИЛИЯ LIKE SUBSTR((select * from (select ФАМИЛИЯ from Н_ЛЮДИ order by dbms_random.value) where rownum<=1),1,2)||'%' and rownum <= 75 order by ФИО DESC;
6.
select ФАМИЛИЯ, ИМЯ, ОТЧЕСТВО, ИД from Н_ЛЮДИ where ИМЯ NOT LIKE 'А%' and ИМЯ NOT LIKE 'Б%' and ИМЯ NOT LIKE 'З%' and ИМЯ NOT LIKE 'К%' and ИМЯ NOT LIKE 'У%'
and ОТЧЕСТВО NOT LIKE 'А%' and ОТЧЕСТВО NOT LIKE 'Б%' and ОТЧЕСТВО NOT LIKE 'З%' and ОТЧЕСТВО NOT LIKE 'К%' and ОТЧЕСТВО NOT LIKE 'У%';

select ФАМИЛИЯ, ИМЯ, ОТЧЕСТВО, ИД from Н_ЛЮДИ where SUBSTR(ИМЯ,1,1) != 'А' and SUBSTR(ИМЯ,1,1) != 'Б' 
and SUBSTR(ИМЯ,1,1) != 'З' and SUBSTR(ИМЯ,1,1) != 'К' and SUBSTR(ИМЯ,1,1) != 'У'
and ОТЧЕСТВО NOT LIKE 'А%' and ОТЧЕСТВО NOT LIKE 'Б%' and ОТЧЕСТВО NOT LIKE 'З%' and ОТЧЕСТВО NOT LIKE 'К%' and ОТЧЕСТВО NOT LIKE 'У%';
7.
select DISTINCT count(ИД) COUNT FROM Н_ЛЮДИ where ИМЯ = (select * from (select ИМЯ from Н_ЛЮДИ order by dbms_random.value) where rownum<=1);
8.
begin
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ 
where ЧЛВК_ИД = CAST((select * from (select ИД from Н_ЛЮДИ order by dbms_random.value) where rownum<=1) AS INT))
loop
if REGEXP_LIKE (marks.ОЦЕНКА, '^зачет$') then dbms_output.put_line('двойной зачет');
elsif marks.ОЦЕНКА not in ('3','4','5') then dbms_output.put_line(marks.ОЦЕНКА||'*2');
else dbms_output.put_line(CAST(marks.ОЦЕНКА AS INT)*2);
end if;
end loop;
end;
/
9.
declare
allmarks INT := 0;
begin
for person in (select * from (select ИД from Н_ЛЮДИ order by dbms_random.value) where rownum<=7)
loop
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ where ЧЛВК_ИД = CAST(person.ИД AS INT))
loop
if marks.ОЦЕНКА in ('3','4','5') then allmarks := allmarks + CAST(marks.ОЦЕНКА AS INT);
end if;
end loop;
end loop;
dbms_output.put_line('Сумма : '||TO_CHAR(allmarks));
end;
/
10.
select Н_УЧЕБНЫЕ_ГОДА.*, Н_ОЦЕНКИ.*, Н_ТИПЫ_ВЕДОМОСТЕЙ.*, Н_ТИПЫ_СТАНДАРТОВ.*, Н_ФОРМЫ_ОБУЧЕНИЯ.*, Н_ТИПЫ_ПЛАНОВ.*, Н_ВИДЫ_ОБУЧЕНИЯ.* 
from Н_УЧЕБНЫЕ_ГОДА, Н_ОЦЕНКИ, Н_ТИПЫ_ВЕДОМОСТЕЙ, Н_ТИПЫ_СТАНДАРТОВ, Н_ФОРМЫ_ОБУЧЕНИЯ, Н_ТИПЫ_ПЛАНОВ, Н_ВИДЫ_ОБУЧЕНИЯ
where rownum <= 100;
11.
declare
sumofmarks INT := 0;
numofmarks INT := 0;
avmark NUMBER := 0;
maincounter INT := 0;
type c_list is varray(5000) of int; 
namesakesids c_list := c_list(); 
counter integer :=0; 
begin
for person in (select * from (select ИД, ФАМИЛИЯ, ИМЯ, ОТЧЕСТВО from Н_ЛЮДИ order by dbms_random.value))
loop
sumofmarks := 0;
numofmarks := 0;
counter := 0;
--dbms_output.put_line('Selected : '||TO_CHAR(person.ИД));
--
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ where ЧЛВК_ИД = CAST(person.ИД AS INT))
loop
if marks.ОЦЕНКА in ('3','4','5') then sumofmarks := sumofmarks + CAST(marks.ОЦЕНКА AS INT);
numofmarks := numofmarks + 1;
end if;
end loop;
if numofmarks = 0 then continue;
end if;
avmark := sumofmarks/numofmarks;
--dbms_output.put_line('Average mark : '||TO_CHAR(avmark));
--
--dbms_output.put_line('Checking for : '||person.ФАМИЛИЯ);
for namesake in (select * from (select ИД, ФАМИЛИЯ from Н_ЛЮДИ) where ФАМИЛИЯ = person.ФАМИЛИЯ)
loop
counter := counter + 1;
namesakesids.extend;
namesakesids(counter) := namesake.ИД;
end loop;
--dbms_output.put_line('Found : '||TO_CHAR(counter));
for lcntr in 1..counter
loop
--dbms_output.put_line('OK ');
--
sumofmarks := 0;
numofmarks := 0;
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ where ЧЛВК_ИД = CAST(namesakesids(lcntr) AS INT))
loop
if marks.ОЦЕНКА in ('3','4','5') then sumofmarks := sumofmarks + CAST(marks.ОЦЕНКА AS INT);
numofmarks := numofmarks + 1;
end if;
end loop;
if numofmarks = 0 then continue;
end if;
--dbms_output.put_line('Current average : '||TO_CHAR(sumofmarks/numofmarks)||' comparing to '||TO_CHAR(avmark));
if sumofmarks/numofmarks > avmark then maincounter := maincounter + 1;
dbms_output.put_line(person.ФАМИЛИЯ||' '||person.ИМЯ||' '||person.ОТЧЕСТВО||' '||TO_CHAR(avmark));
exit;
end if;
--
end loop;
if maincounter >= 7 then exit;
end if;
end loop;
end;
/
12.
select * from Н_УЧЕБНЫЕ_ГОДА;
select * from Н_ВЕДОМОСТИ;
declare
sumofgoodmarks INT := 0;
numofgoodmarks INT := 0;
numofz INT := 0;
counter INT := 0;
hasthrees BOOLEAN := FALSE;
hasfours BOOLEAN := FALSE;
hasfives BOOLEAN := FALSE;
personcounter INT := 0;
sumofdistances INT := 0;
begin
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ)
loop
if marks.ОЦЕНКА in ('4','5') then sumofgoodmarks := sumofgoodmarks + CAST(marks.ОЦЕНКА AS INT);
numofgoodmarks := numofgoodmarks + 1;
end if;
end loop;
for year in (select * from (select НАЧАЛО, КОНЕЦ from Н_УЧЕБНЫЕ_ГОДА order by dbms_random.value) where rownum <= 1)
loop
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ where ДАТА < year.КОНЕЦ and ДАТА > year.НАЧАЛО)
loop
if marks.ОЦЕНКА = 'зачет' then numofz := numofz + 1;
end if;
end loop;
end loop;
for person in (select * from (select ИД, ФАМИЛИЯ, ИМЯ, ОТЧЕСТВО from Н_ЛЮДИ order by dbms_random.value))
loop
hasthrees := FALSE;
hasfours := FALSE;
hasfives := FALSE;
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ where ЧЛВК_ИД = CAST(person.ИД AS INT))
loop
if marks.ОЦЕНКА = '3' then hasthrees := TRUE;
elsif marks.ОЦЕНКА = '4' then hasfours := TRUE;
elsif marks.ОЦЕНКА = '5' then hasfives := TRUE;
end if;
end loop;
if hasthrees and hasfours and hasfives then personcounter := personcounter + 1;
sumofdistances := sumofdistances + UTL_MATCH.EDIT_DISTANCE(person.ФАМИЛИЯ, 'Плюхин');
end if;
if personcounter >= 10 then exit;
end if;
end loop;
dbms_output.put_line(chr(9)||chr(9)||chr(9)||chr(9)||chr(9)||'Средняя оценка'||chr(9)||chr(9)||'Количество оценок');
dbms_output.put_line('Оценки 4 и 5 во всем университете'||chr(9)||chr(9)||TO_CHAR(ROUND(sumofgoodmarks/numofgoodmarks,2))
||chr(9)||chr(9)||chr(9)||'     '||TO_CHAR(numofgoodmarks));
dbms_output.put_line('Оценки ''зачет'' в произвольном'||chr(13)||chr(10)||'учебном году во всем университете'
||chr(9)||chr(9)||'    '||'-'||chr(9)||chr(9)||chr(9)||chr(9)||TO_CHAR(numofz));
dbms_output.put_line('Расстояние Левенштайна до вашей'||chr(13)||chr(10)||'фамилии от фамилии 10 персон,'||chr(13)||chr(10)||'имеющих оценки 3, 4, 5'
||chr(9)||chr(9)||chr(9)||chr(9)||chr(9)||'      '||TO_CHAR(ROUND(sumofdistances/personcounter, 0))||chr(9)||chr(9)||chr(9)||chr(9)||'     '||'-');
--dbms_output.put_line('Average among 4 and 5: '||TO_CHAR(sumofgoodmarks/numofgoodmarks));
--dbms_output.put_line('Number of 4 and 5 : '||TO_CHAR(numofgoodmarks));
--dbms_output.put_line('Number of zachets in random year : '||TO_CHAR(numofz));
--dbms_output.put_line(TO_CHAR(ROUND(sumofdistances/personcounter, 0)));
end;
/
13.
declare
begin
for person in (select * from (select ИД, ФАМИЛИЯ||' '||ИМЯ||' '||ОТЧЕСТВО ФИО from Н_ЛЮДИ order by ФИО))
loop
for marks in (select ОЦЕНКА, ДАТА from Н_ВЕДОМОСТИ where ЧЛВК_ИД = CAST(person.ИД AS INT))
loop
if marks.ОЦЕНКА in ('3', '4') and marks.ДАТА > TO_DATE('01.09.2016') and marks.ДАТА < TO_DATE('27.07.2017') then dbms_output.put_line(person.ФИО);
exit;
end if;
end loop;
end loop;
end;
/
14.
declare
boundsum INT := 0;
counter INT := 0;
sumofmarks INT := 0;
begin
for person in (select * from (select ИД from Н_ЛЮДИ order by dbms_random.value) where rownum<=1)
loop
--dbms_output.put_line(TO_CHAR(person.ИД));
for i in 1..6
loop
boundsum := boundsum + CAST(SUBSTR(TO_CHAR(person.ИД),i,1) AS INT);
end loop;
--dbms_output.put_line(TO_CHAR(boundsum));
end loop;
for combination in (select * from (select ФИО, COUNT(ФИО) ПОВТОРЕНИЯ from (select ФАМИЛИЯ||' '||ИМЯ||' '
||ОТЧЕСТВО ФИО from Н_ЛЮДИ) group by ФИО order by ПОВТОРЕНИЯ DESC) where ПОВТОРЕНИЯ > 1)
loop
--dbms_output.put_line(combination.ФИО);
sumofmarks := 0;
for person in (select ИД from Н_ЛЮДИ where ФАМИЛИЯ||' '||ИМЯ||' '||ОТЧЕСТВО = combination.ФИО)
loop
sumofmarks := 0;
for marks in (select ОЦЕНКА from Н_ВЕДОМОСТИ where ЧЛВК_ИД = CAST(person.ИД AS INT))
loop
if marks.ОЦЕНКА in ('3','4','5') then sumofmarks := sumofmarks + CAST(marks.ОЦЕНКА AS INT);
end if;
end loop;
--dbms_output.put_line(TO_CHAR(sumofmarks));
if sumofmarks <= boundsum then dbms_output.put_line(person.ИД||' '||combination.ФИО);
end if;
end loop;
counter := counter + 1;
end loop;
end;
/