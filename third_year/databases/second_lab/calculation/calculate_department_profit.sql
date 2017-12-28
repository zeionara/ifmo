select ид, название, lab2_db.calculate_department_quantity_profit(ид) количество_проданного_товара, 
	lab2_db.calculate_department_profit(ид) прибыль from отделы
	order by прибыль desc;
