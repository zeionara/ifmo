1.
alter session set NLS_DATE_FORMAT = 'dd.mm.yyyy HH24:mi:ss';
SELECT * FROM м_яеяяхъ;
2.
SELECT DISTINCT мюхлемнбюмхе FROM м_дхяжхокхмш;
3.
#select дюрю_пнфдемхъ from м_кчдх where rownum <= 1
#select DATEDIFF(day, '2017-08-01 00:00:00', '2017-09-01 00:00:00')
#SELECT TO_DATE('05.07.2007 09:53:01')-TO_DATE('05.08.2007 09:53:01') FROM м_кчдх;
#SELECT TO_DATE('05.07.2007 09:53:01')-TO_DATE('05.08.2007 09:53:01') AS DIFF FROM м_кчдх where rownum<=1;
#SELECT TO_DATE('01.09.2017 00:00:00')-(select дюрю_пнфдемхъ from м_кчдх where rownum <= 1) AS DIFF FROM м_кчдх where rownum<=1;
SELECT TO_DATE('01.09.2017 00:00:00')-(select * from (select дюрю_пнфдемхъ from м_кчдх order by dbms_random.value) where rownum <= 1) AS DIFF FROM м_кчдх where rownum<=1;
4.
select тюлхкхъ||' '||SUBSTR(хлъ,1,1)||'.'||SUBSTR(нрвеярбн,1,1)||'.' тюлхкхъ_х_хмхжхюкш from м_кчдх 
where EXTRACT(month from дюрю_пнфдемхъ) = (select * from (select EXTRACT(month from дюрю_пнфдемхъ) леяъж from м_кчдх order by dbms_random.value) where rownum<=1);
5.
SELECT SUBSTR((select * from (select тюлхкхъ from м_кчдх order by dbms_random.value) where rownum<=1),1,2)||'%' FROM м_кчдх;
select тюлхкхъ||' '||хлъ||' '||нрвеярбн тхн, хд FROM м_кчдх 
where тюлхкхъ LIKE SUBSTR((select * from (select тюлхкхъ from м_кчдх order by dbms_random.value) where rownum<=1),1,2)||'%' and rownum <= 75 order by тхн DESC;
6.
select тюлхкхъ, хлъ, нрвеярбн, хд from м_кчдх where хлъ NOT LIKE 'ю%' and хлъ NOT LIKE 'а%' and хлъ NOT LIKE 'г%' and хлъ NOT LIKE 'й%' and хлъ NOT LIKE 'с%'
and нрвеярбн NOT LIKE 'ю%' and нрвеярбн NOT LIKE 'а%' and нрвеярбн NOT LIKE 'г%' and нрвеярбн NOT LIKE 'й%' and нрвеярбн NOT LIKE 'с%';

select тюлхкхъ, хлъ, нрвеярбн, хд from м_кчдх where SUBSTR(хлъ,1,1) != 'ю' and SUBSTR(хлъ,1,1) != 'а' 
and SUBSTR(хлъ,1,1) != 'г' and SUBSTR(хлъ,1,1) != 'й' and SUBSTR(хлъ,1,1) != 'с'
and нрвеярбн NOT LIKE 'ю%' and нрвеярбн NOT LIKE 'а%' and нрвеярбн NOT LIKE 'г%' and нрвеярбн NOT LIKE 'й%' and нрвеярбн NOT LIKE 'с%';
7.
select DISTINCT count(хд) COUNT FROM м_кчдх where хлъ = (select * from (select хлъ from м_кчдх order by dbms_random.value) where rownum<=1);
8.
select CAST(нжемйю AS INT)*2 сдбнеммюъ_нжемйю from (select нжемйю from м_беднлнярх 
where вкбй_хд = CAST((
    select * from (
        select хд from м_кчдх 
        order by dbms_random.value
    ) where rownum<=1
) AS INT) AND нжемйю IN ('3','4','5'));
9.
with
extra as (select * from (select хд from м_кчдх order by dbms_random.value) where rownum<=7)
select вкбй_хд, SUM(нжемйю) from (
    select вкбй_хд,
    case when нжемйю IN ('3','4','5') then нжемйю else '0' end нжемйю
    from м_беднлнярх union all (select * from (extra cross join (select '0' нжемйю from dual)))
)
where вкбй_хд IN (select * from extra)
group by вкбй_хд;
11.
with
people_fragment as (select хд, хлъ, тюлхкхъ, нрвеярбн from м_кчдх),
marks_fragment as (select вкбй_хд хд, AVG(нжемйю) япедмъъ_нжемйю from (
    select вкбй_хд, нжемйю
    from м_беднлнярх
    where нжемйю IN ('3','4','5')
) group by вкбй_хд),
main_table as (select people_fragment.хд, хлъ, тюлхкхъ, нрвеярбн, япедмъъ_нжемйю
from (people_fragment inner join marks_fragment on people_fragment.хд = marks_fragment.хд)),
max_by_families as (select тюлхкхъ, MAX(япедмъъ_нжемйю) люйя_нжемйю from main_table group by тюлхкхъ),
clean_table as (select * from main_table where (тюлхкхъ, япедмъъ_нжемйю) not in (select тюлхкхъ, люйя_нжемйю япедмъъ_нжемйю from max_by_families))
select * from (select тюлхкхъ, хлъ, нрвеярбн, япедмъъ_нжемйю from clean_table order by dbms_random.value) where rownum<=7;
12.
with
threes as (select вкбй_хд хд from м_беднлнярх where нжемйю = '3'),
fours as (select вкбй_хд хд from м_беднлнярх where нжемйю = '4'),
fives as (select вкбй_хд хд from м_беднлнярх where нжемйю = '5'),
people as (select тюлхкхъ from м_кчдх 
where хд in (select * from threes) and хд in (select * from fours) and хд in (select * from fives) order by dbms_random.value),
random_people as (select * from (select * from people order by dbms_random.value) where rownum<=7),
avg_mark as (select AVG(нжемйю) гмв from (select нжемйю from м_беднлнярх where нжемйю in ('4','5'))),
avg_dist as (select AVG(UTL_MATCH.EDIT_DISTANCE(тюлхкхъ, 'оКЧУХМ')) гмв from random_people),
num_of_marks as (select COUNT(нжемйю) гмв from (select нжемйю from м_беднлнярх where нжемйю in ('4','5'))),
random_year as (select * from (select мювюкн, йнмеж from м_свеамше_цндю order by dbms_random.value) where rownum <= 1),
marks_count as (select COUNT(дюрю) гмв from random_year, м_беднлнярх where нжемйю = 'ГЮВЕР' and дюрю > мювюкн and дюрю < йнмеж),
first_row as (select 'нЖЕМЙХ 4 Х 5 БН БЯЕЛ СМХБЕПЯХРЕРЕ' мюхлемнбюмхе, ROUND(avg_mark.гмв,2) япедмъъ_нжемйю, num_of_marks.гмв йнкхвеярбн_нжемнй 
from dual, avg_mark, num_of_marks),
second_row as (select 'нЖЕМЙХ "ГЮВЕР" Б ОПНХГБНКЭМНЛ СВЕАМНЛ ЦНДС БН БЯЕЛ СМХБЕПЯХРЕРЕ' мюхлемнбюмхе, 
null япедмъъ_нжемйю, marks_count.гмв йнкхвеярбн_нжемнй from dual, marks_count),
third_row as (select 'пЮЯЯРНЪМХЕ кЕБЕМЬРЮИМЮ ДН БЮЬЕИ ТЮЛХКХХ НР ТЮЛХКХИ 10 ОЕПЯНМ, ХЛЕЧЫХУ НЖЕМЙХ 3, 4 Х 5' мюхлемнбюмхе, 
ROUND(avg_dist.гмв, 2) япедмъъ_нжемйю, null йнкхвеярбн_нжемнй from dual, avg_dist)
select * from (((select * from first_row) union all (select * from second_row)) union all (select * from third_row));
13.
with
ids as (select distinct вкбй_хд from м_беднлнярх where нжемйю IN ('3','4') and TO_DATE('01.09.06') < дюрю and TO_DATE('20.07.07') > дюрю)
select тюлхкхъ||' '||хлъ||' '||нрвеярбн тхн from м_кчдх where хд in (select * from ids) order by тхн;
14.
with
random_id as (select * from (select хд from м_кчдх order by dbms_random.value) where rownum<=1),
sum_random_id as (select SUBSTR(хд,1,1)+SUBSTR(хд,2,1)+SUBSTR(хд,3,1)+SUBSTR(хд,4,1)+SUBSTR(хд,5,1)+SUBSTR(хд,6,1) гмв from random_id),
peop_sum as (select * from (select SUM(нжемйю) ясл, 
вкбй_хд from м_беднлнярх, sum_random_id where нжемйю in ('3','4','5') group by вкбй_хд), sum_random_id),
peop_needed as (select вкбй_хд from peop_sum where гмв > ясл),
repeatings as (select * from (select COUNT(тхн) онбрнпемхъ, тхн 
from (select тюлхкхъ||' '||хлъ||' '||нрвеярбн тхн from м_кчдх) group by тхн order by онбрнпемхъ desc) where онбрнпемхъ > 1),
peop_fio as (select тюлхкхъ||' '||хлъ||' '||нрвеярбн тхн, хд from м_кчдх)
select хд, repeatings.тхн from (repeatings inner join peop_fio on repeatings.тхн = peop_fio.тхн) where хд in (select * from peop_needed);