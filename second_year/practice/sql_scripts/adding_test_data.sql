DROP PROCEDURE IF EXISTS `random_data`;
DELIMITER $$
CREATE PROCEDURE `random_data`(IN counter INTEGER(11))
BEGIN
    DECLARE name NVARCHAR(255);
    DECLARE surname NVARCHAR(255);
    DECLARE patronymic NVARCHAR(255);
    DECLARE russian boolean;
    DECLARE italian boolean;
    DECLARE japanese boolean;
    DECLARE morningshifts boolean;
    DECLARE eveningshifts boolean;
    DECLARE necessityshiftstime boolean;
    DECLARE dayduration int(2);
    DECLARE necessitydayduration boolean;
    DECLARE workingmode_5_2 boolean;
    DECLARE workingmode_2_2 boolean;
    DECLARE id INT;

    SET id = 1;
    WHILE id < counter DO

        SET name = CONCAT_WS('',CHAR(ROUND(RAND()*25)+65),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97));
        SET surname = CONCAT(CONCAT_WS('',CHAR(ROUND(RAND()*25)+65),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97)),"ev");
        SET patronymic = CONCAT_WS('',CHAR(ROUND(RAND()*25)+65),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97),CHAR(ROUND(RAND()*25)+97));
        SET russian = ROUND(RAND());
        SET italian = ROUND(RAND());
        SET japanese = ROUND(RAND());
        SET morningshifts = ROUND(RAND());
        SET eveningshifts = 1 - morningshifts;
        SET necessityshiftstime = ROUND(RAND());
        SET dayduration = ROUND(RAND()*6)+4;
        SET necessitydayduration = ROUND(RAND());
        SET workingmode_5_2 = ROUND(RAND());
        SET workingmode_2_2 = 1 - workingmode_5_2;

        INSERT INTO cooks_test_1 (name, surname, patronymic, russian, italian, japanese, morningshifts, eveningshifts,
		necessityshiftstime, dayduration, necessitydayduration, workingmode_5_2, workingmode_2_2) VALUES
        (name, surname, patronymic, russian, italian, japanese, morningshifts, eveningshifts,
		necessityshiftstime, dayduration, necessitydayduration, workingmode_5_2, workingmode_2_2);
        SET id = id + 1;
    END WHILE;
END;$$
DELIMITER ;
CALL random_data(1000);
