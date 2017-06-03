create table cooks(
	cookid int not null auto_increment primary key,
	name nvarchar(50) not null,
	surname nvarchar(50) not null,
	patronymic nvarchar(60) null,
	russian boolean not null,
	italian boolean not null,
	japanese boolean not null,
	morningshifts boolean not null,
	eveningshifts boolean not null,
	necessityshiftstime boolean not null,
	dayduration int(2) not null,
	necessitydayduration boolean not null,
	workingmode_5_2 boolean not null,
	workingmode_2_2 boolean not null
);
