IF db_id('SI2_TP1') is null
	CREATE DATABASE SI2_TP1;
GO

use SI2_TP1
set dateformat dmy;

--if OBJECT_ID('PREFERENCES') IS NOT NULL
  
-- ADDRESS AND COUNTRY TABLES
create table COUNTRY(
	ID			int identity(1,1),
	NAME		char(50),
	constraint pk_COUNTRY primary key (ID)
)
create table ADDRESS(
	ID			int identity(1,1),
	STREET		varchar(80),
	ZIP_CODE	char(15),
	CITY		char(30),
	COUNTRY_ID	int not null,
	constraint pk_ADDRESS primary key (ID),
	constraint fk_ADDRESS foreign key (COUNTRY_ID) references COUNTRY(ID)
)

--CUSTOMER(ID[PK],NAME,CONTACT,ADDRESS,TYPE);
create table CUSTOMER(
	ID			int identity(1,1),
	NAME		char(50) not null,
	CONTACT		int not null,
	-- CUSTOMER TYPE: 0 - registered, 1 - normal
	CUSTOMER_TYPE tinyint check (CUSTOMER_TYPE >=0 AND CUSTOMER_TYPE <2),
	constraint pk_CUSTOMER primary key (ID),
)

--COURSES(ID[PK], NAME, ACTIVE, VALUE);
create table COURSES(
	ID			int identity(1,1),
	NAME		varchar(30) not null,
	ACTIVE		bit not null,
	VALUE		smallmoney not null,	-- Preço de venda da porção
	constraint  pk_COURSES primary key (ID),
)

--COMMENTS(ID[PK], CUSTOMER_ID[FK], COURSES_ID[FK], GRADE, COMMENT);
create table COMMENTS(
	ID			int identity(1,1),
	CUSTOMER_ID	int not null,
	COURSES_ID	int not null,
	GRADE		tinyint check (GRADE >0 AND GRADE <6),
	COMMENT		varchar(200),
	constraint  pk_COMMENTS primary key (ID),
	constraint	fk_COMMENTS1 foreign key(CUSTOMER_ID) references CUSTOMER(ID),
	constraint	fk_COMMENTS2 foreign key(COURSES_ID) references COURSES(ID)
)
--MEETING(ID[PK],COMMENT_ID[FK], DATE,DETAILS);
create table MEETING(
	ID			int identity(1,1),
	COMMENT_ID	int not null,
	DATE		date not null,
	DETAILS		varchar(800),
	constraint  pk_MEETING primary key (ID),
	constraint	fk_MEETING foreign key(COMMENT_ID) references COMMENTS(ID) 
)

--REGISTERED(CUSTOMER_ID[FK], ADDRESS_ID[FK]);
create table REGISTERED(
	CUSTOMER_ID	int not null,
	ADDRESS_ID	int not null,
	constraint	pk_REGISTERED primary key (CUSTOMER_ID),
	constraint	fk_REGISTERED1 foreign key (CUSTOMER_ID) references CUSTOMER(ID),
	constraint	fk_REGISTERED2 foreign key(ADDRESS_ID) references ADDRESS(ID)
)

--BOOKING(ID[PK], CUSTOMER_ID[FK], DATE, QTY,TYPE);			//VALIDAR/INCREMENTAR/DECREMENTAR CONFORME SÃO FEITAS AS RESPOSTAS. // FALTA A RELAÇÃO ENTRE EVENTO E OS SEU CONVIDADOS.
create table BOOKING(
	ID			int identity(1,1),
	CUSTOMER_ID	int not null,
	DATE		date not null,
	QTY			tinyint not null,
	-- Booking_Type: 0 - Normal Booking; 1 - Event
	BOOKING_TYPE tinyint check (BOOKING_TYPE >=0 AND BOOKING_TYPE <2),
	-- Status: 0 - PENDING; 1 - CONFIRMED; 2 - CANCELED
	STATUS		tinyint default(0) check (STATUS>=0 AND STATUS <=2) not null,	
	constraint  pk_BOOKING primary key (ID),
	constraint	fk_BOOKING foreign key(CUSTOMER_ID) references CUSTOMER(ID),
)

--MENU(ID[PK], NAME, TYPE);
create table MENU(
	ID			int identity(1,1),
	NAME		char(30) not null,
	TYPE		char(30) not null,
	constraint  pk_MENU primary key (ID),
)

--EVENT(BOOKING_ID[FK], MENU_ID[FK], NAME, DESCRIPTION);

create table EVENT(
	BOOKING_ID	int not null,
	MENU_ID		int not null,
	NAME		char(30) not null,
	DESCRIPTION varchar(200) not null,
	constraint  pk_EVENT primary key(BOOKING_ID),
	constraint	fk_EVENT1 foreign key(BOOKING_ID) references BOOKING(ID),
	constraint	fk_EVENT2 foreign key(MENU_ID) references MENU(ID)
)
--//NORMAL_BOOKING(BOOKING_ID[FK], MENU_ID[FK]); //pode ter ou não menu escolhido à partida
create table NORMAL_BOOKING(
	BOOKING_ID	int not null,
	MENU_ID		int,
	constraint  pk_NORMAL_BOOKING primary key(BOOKING_ID),
	constraint	fk_NORMAL_BOOKING1 foreign key(BOOKING_ID) references BOOKING(ID),
	constraint	fk_NORMAL_BOOKING2 foreign key(MENU_ID) references MENU(ID)	
)

-- UNIT(ID[PK], UNIT)
create table UNIT(
	ID			int identity(1,1),
	UNIT		char(3) not null,
	constraint	pk_UNIT primary key(ID)
)

--INGREDIENTS(ID[PK], NAME, QTY_RESERVED, UNIT_ID[FK]);
create table INGREDIENTS(
	ID			int identity(1,1),
	NAME		char(30) not null,
	QTY_RESERVED float default(0) not null,
	UNIT_ID		int not null,
	constraint  pk_INGREDIENTS primary key (ID),
	constraint  fk_INGREDIENTS foreign key(UNIT_ID) references UNIT(ID)
)

--SUPPLIERS(ID[PK], NAME, ADDRESS_ID[FK], DELIVERY_DAYS, PAYMENT_TERMS);
create table SUPPLIERS(
	ID			int identity(1,1),
	NAME		char(30) not null,
	ADDRESS_ID	int not null,
	constraint pk_SUPPLIERS primary key (ID),
	constraint fk_SUPPLIERS foreign key(ADDRESS_ID) references ADDRESS(ID),
)
-- LOT(ID[PK], INGREDIENTS_ID[FK], SUPPLIER_ID[FK], INVOICE, DATE, QTY, PRICE, VALIDITY, STOCK)
-- LOT replaces purchases: has info on buys, atual stock and validity date
--PURCHASES(ID[PK], INVOICE, DATE, SUPPLIER_ID[FK], INGREDIENTS_ID[FK], QTY, VALIDITY, PRICE);
create table LOT(
	ID				int identity(1,1),
	INGREDIENTS_ID	int not null,
	SUPPLIER_ID		int not null,
	INVOICE			int not null,
	DATE			date not null,
	QTY				float default(0) not null,
	PRICE			smallmoney default(0) not null,
	VALIDITY		date not null,
	STOCK			float default(0) not null,
	constraint pk_LOT primary key (ID),
	constraint fk_LOT foreign key(SUPPLIER_ID) references SUPPLIERS(ID),
	constraint fk_LOT1 foreign key(INGREDIENTS_ID) references INGREDIENTS(ID)
)

--ORDERS(ID[PK],SUPPLIER_ID[FK], INGREDIENT_ID[FK], DATE, QTY_ORDERED, EXPECTED_DATE);			//e as entregas parciais?? //falta tabela _LOG
create table ORDERS(
	ID			int identity(1,1),
	SUPPLIER_ID int not null,
	INGREDIENT_ID int not null,
	DATE		date not null,
	QTY_ORDERED tinyint not null,
	EXPECTED_DATE date not null,
	constraint pk_ORDERS primary key (ID),
	constraint fk_ORDERS1 foreign key(SUPPLIER_ID) references SUPPLIERS(ID),
	constraint fk_ORDERS2 foreign key(INGREDIENT_ID) references INGREDIENTS(ID)
)

--ORDERS_LOG(ID[PK],SUPPLIER_ID[FK], INGREDIENT_ID[FK], DATE, QTY_ORDERED, EXPECTED_DATE, INVOICE_ID[FK]);
create table ORDERS_LOG(
	ID			int identity(1,1),
	SUPPLIER_ID int not null,
	INGREDIENTS_ID int not null,
	DATE		date not null,
	QTY_ORDERED tinyint not null,
	EXPECTED_DATE date not null,
	LOT_ID		int not null,
	constraint pk_ORDERS_LOG primary key (ID),
	constraint fk_ORDERS_LOG1 foreign key(SUPPLIER_ID) references SUPPLIERS(ID),
	constraint fk_ORDERS_LOG2 foreign key(INGREDIENTS_ID) references INGREDIENTS(ID),
	constraint fk_ORDERS_LOG3 foreign key(LOT_ID) references LOT(ID)
)

--COURSES_INGREDIENTS(COURSES_ID[FK], INGREDIENTS_ID[FK], QTY);	//VERIFICAR PREÇO QUANDO HÁ ALTERAÇÕES DE PREÇO NA COMPRA DE INGREDIENTES.
create table COURSES_INGREDIENTS(
	COURSES_ID		int not null,
	INGREDIENTS_ID	int not null,
	QTY				float default(0) not null,
	constraint pk_COURSES_INGREDIENTS primary key (COURSES_ID, INGREDIENTS_ID),
	constraint fk_COURSES_INGREDIENTS1 foreign key(COURSES_ID) references COURSES(ID),
	constraint fk_COURSES_INGREDIENTS2 foreign key(INGREDIENTS_ID) references INGREDIENTS(ID)
)

--MENU_COURSES(COURSES_ID[FK],MENU_ID[FK]);
create table MENU_COURSES(
	MENU_ID		int not null,
	COURSES_ID	int not null,
	constraint pk_MENU_COURSES primary key (COURSES_ID, MENU_ID),
	constraint fk_MENU_COURSES1 foreign key(MENU_ID) references MENU(ID),
	constraint fk_MENU_COURSES2 foreign key(COURSES_ID) references COURSES(ID)
)

--FRIENDS(REGISTERED_ID1[FK],REGISTERED_ID2[FK]) ;
create table FRIENDS(
	REGISTERED_ID1	int not null,
	REGISTERED_ID2	int not null,
	constraint pk_FRIENDS primary key (REGISTERED_ID1, REGISTERED_ID2),
	constraint fk_FRIENDS1 foreign key(REGISTERED_ID1) references REGISTERED(CUSTOMER_ID),
	constraint fk_FRIENDS2 foreign key(REGISTERED_ID2) references REGISTERED(CUSTOMER_ID)
)

--EVENT_FRIENDS(BOOKING_ID[FK], CUSTOMER_ID[FK], STATUS);
create table EVENT_FRIENDS(
	BOOKING_ID	int not null,
	CUSTOMER_ID int not null,
	--0: not confirmed; 1: confirmed
	STATUS		tinyint default(0) not null,  
	constraint pk_EVENT_FRIENDS primary key (BOOKING_ID, CUSTOMER_ID),
	constraint fk_EVENT_FRIENDS foreign key(BOOKING_ID) references BOOKING(ID),
	constraint fk_EVENT_FRIENDS1 foreign key(CUSTOMER_ID) references CUSTOMER(ID)
)

create table PREFERENCES(
	ID						int identity(1,1),
	MIN_EVENT_CUSTOMER 		int default(0) not null,
	MAX_NUMBER_CUSTOMERS 	int default(100) not null,
	constraint pk_PREFERENCES primary key (ID)
)

create table EVENT_DISCOUNTS(
	ID						int identity(1,1),
	CUSTOMER_QTY			int check (CUSTOMER_QTY>=0) default(0) not null,
	DISCOUNT				float check (DISCOUNT>=0) default(0) not null,
	constraint pk_EVENT_DISCOUNTS primary key (ID)
)

--////BOOKING_MENU(BOOKING_ID[FK]); // SIMPLIFICAÇÃO: RESERVA(ID[PK],CARDAPIO_ID[FK], DATA, NUMERO_PESSOAS, CONFIRMACOES,TIPO);
--////COMMENT_CUSTOMER(COMMENT_ID[FK]);	//SIMPLIFICAÇÃO: COMENTARIO(ID[PK], ID_CLIENTE[FK],OBS,NOTA);
--////MEETING_COMMENT(MEETING_ID[FK],MEETING_DATE[FK]);	// SIMPLIFICAÇÃO: REUNIAO(ID[PK],ID_COMENTARIO[FK], DATA,CONCLUSAO);


