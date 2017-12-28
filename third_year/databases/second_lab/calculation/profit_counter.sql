DELIMITER $$

	DROP FUNCTION IF EXISTS `calculate_worker_profit`$$

    CREATE  FUNCTION `calculate_worker_profit`(
	worker_id INT	
    ) RETURNS INT
    BEGIN
		DECLARE whole_amount INT DEFAULT 0;
        select sum(количество*цена) into whole_amount from таблица_3 where ид_человека = worker_id;
		RETURN whole_amount;
    END$$
    
    DROP FUNCTION IF EXISTS `calculate_worker_quantity_profit`$$

    CREATE  FUNCTION `calculate_worker_quantity_profit`(
	worker_id INT	
    ) RETURNS INT
    BEGIN
		DECLARE whole_amount INT DEFAULT 0;
        select sum(количество) into whole_amount from таблица_3 where ид_человека = worker_id;
		RETURN whole_amount;
    END$$


    DROP FUNCTION IF EXISTS `calculate_department_profit`$$

    CREATE  FUNCTION `calculate_department_profit`(
	department_id INT	
    ) RETURNS INT
    BEGIN
		DECLARE whole_amount INT DEFAULT 0;
        
        select sum(lab2_db.calculate_worker_profit(ид_человека)) into whole_amount from 
        (select distinct ид_человека from (select * from таблица_2 where ид in 
		(select мид from (select min(ид) мид, ид_человека from таблица_2 group by ид_человека) as t)
        ) as r where ид_отдела = department_id) as t;
		RETURN whole_amount;
    END$$
    
    DROP FUNCTION IF EXISTS `calculate_department_quantity_profit`$$

    CREATE  FUNCTION `calculate_department_quantity_profit`(
	department_id INT	
    ) RETURNS INT
    BEGIN
		DECLARE whole_amount INT DEFAULT 0;
        
        select sum(lab2_db.calculate_worker_quantity_profit(ид_человека)) into whole_amount from 
        (select ид_человека from (select * from таблица_2 where ид in 
		(select мид from (select min(ид) мид, ид_человека from таблица_2 group by ид_человека) as t)
        ) as r where ид_отдела = department_id) as t;
		RETURN whole_amount;
    END$$

    DELIMITER ;