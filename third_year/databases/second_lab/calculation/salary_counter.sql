 DELIMITER $$
 
	DROP FUNCTION IF EXISTS `calculate_daily_salary`$$

    CREATE  FUNCTION `calculate_daily_salary`(
	worker_state varchar(20),
    worker_id int
    ) RETURNS INT
    BEGIN
		DECLARE daily_salary INT DEFAULT 0;
        if (worker_state LIKE 'отпуск') then 
        begin
			select отпускные_за_день into daily_salary from зарплаты where ид_человека = worker_id;
            RETURN daily_salary;
		end;
        end if;
		if (worker_state LIKE 'больничный') then 
        begin
			select больничные_за_день into daily_salary from зарплаты where ид_человека = worker_id;
            RETURN daily_salary;
		end;
        end if;
        if (worker_state IS NULL) then 
        begin
			select зарплата_за_день into daily_salary from зарплаты where ид_человека = worker_id;
            RETURN daily_salary;
		end;
        end if;
        if (worker_state LIKE 'командировка') then 
        select командировочные_за_день into daily_salary from зарплаты where ид_человека = worker_id;
        end if;
		RETURN daily_salary;
    END$$


    DROP FUNCTION IF EXISTS `calculate_salary`$$

    CREATE  FUNCTION `calculate_salary`(
	worker_id INT	
    ) RETURNS INT
    BEGIN
		DECLARE done INT DEFAULT 0;
        DECLARE result varchar(20);
        DECLARE salary INT DEFAULT 0;
        DECLARE daily_salary INT DEFAULT 0;
		select день_1 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_2 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_3 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_4 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_5 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_6 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_7 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_8 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_9 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_10 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_11 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_12 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_13 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_14 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_15 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_16 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_17 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_18 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_19 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_20 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_21 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_22 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_23 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_24 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_25 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_26 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_27 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_28 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_29 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        select день_30 into result from таблица_2 where ид_человека = worker_id limit 1;
        select calculate_daily_salary(result, worker_id) into daily_salary;
        set salary = salary + daily_salary;
        #call debug_msg(@enabled, "my first debug message");
        #insert into tmptable SELECT concat('myvar is ','22');
		#select result;
		RETURN salary;
    END$$

    DELIMITER ;
    