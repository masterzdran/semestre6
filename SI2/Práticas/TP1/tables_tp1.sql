use db_si_ap;

--Cliente(IDCliente[AK], Contacto, Nome)
create table cliente(
	idcliente int identity(1,1),
	nome varchar(128),
	contacto int,
	--constraint
	primary key (idcliente)
)

--Comentario(IDComentario[AK], IDCliente[FK], Nota, Observacoes)
create table comentario(
	idcomentario int identity(1,1),
	nota tinyint check (nota >0 AND nota < 6),
	idcliente int,
	--constraint
	primary key (idcomentario),
	foreign key(idcliente) references cliente(idcliente)
)

--Reuniao(IDReserva[AK], Data], Conclusao, IDComentario[FK])
create table reuniao(
	idreserva int identity(1,1),
	data datetime,
	conclusao varchar(256),
	idcomentario int,
	primary key (idreserva),
	foreign key(idcomentario) references comentario(idcomentario)
)

--CLienteRegistado(IDCliente[AK][FK], Endereco_Postal, Nacionalidade)
create table clienteregistado(
	idcliente int,
	endereco_postal varchar(56),
	nacionalidade varchar(56),
	--constraint
	primary key(idcliente),
	foreign key(idcliente) references cliente(idcliente)
)

--Cardapio(IDCardapio[AK], Descricao, Categoria)
create table cardapio(
	idcardapio int identity(1,1),
	descricao varchar(256),
	categoria varchar(256),
	primary key(idcardapio)
)

--ReservaNormal(IDReserva[AK], IDCardapio[FK], Data, QtdPessoas)
create table reservanormal(
	idreserva int identity(1,1),
	idcardapio int,
	data datetime,
	qtdpessoas int,
	primary key(idreserva),
	foreign key(idcardapio) references cardapio(idcardapio),
)

--Cli_R(IDCliente[AK][FK],IDReserva[AK][FK])
create table cli_r(
	idcliente int,
	idreserva int
	primary key(idcliente, idreserva),
	foreign key(idcliente) references cliente(idcliente),
	foreign key(idreserva) references reservanormal(idreserva)
)

--Amigos(IDCliente[AK][FK], IDAmigo[AK][FK])
create table amigos(
	idcliente int,
	idamigo int,
	--constraint
	primary key(idcliente,idamigo),
	foreign key(idcliente) references cliente(idcliente),
	foreign key(idamigo) references cliente(idcliente)
)

--ReservaEvento(IDReserva[AK][FK], Organizador[FK], Designacao, Descricao)
create table reservaevento(
	idreserva int,
	organizador int,
	designacao varchar(128),
	descricao varchar(256),
	primary key(idreserva),
	foreign key(idreserva) references reservanormal(idreserva),
	foreign key(organizador) references cliente(idcliente)
)

--Pratos(IDPrato[AK], Preco, Qtd, Activo)
create table pratos(
	idprato int identity(1,1),
	preco decimal(12,5),
	qtd smallint,
	activo bit,
	primary key(idprato)
)
		
--Car_P(IDCardapio[AK][FK], IDPrato[AK][FK])
create table car_p(
	idcardapio int,
	idprato int
	primary key(idcardapio,idprato),
	foreign key(idcardapio) references cardapio(idcardapio),
	foreign key(idprato) references pratos(idprato)
)

--Ingredientes(IDIngrediente[AK], Nome, Descricao, Qtd_Reserva, Qtd_Actual)
create table ingredientes(
	idingrediente int identity(1,1),
	nome varchar(128),
	descricao varchar(256),
	qtd_reserva int,
	qtd_actual int
	primary key(idingrediente)
)

--P_I(IDPrato[AK][FK], IDIngrediente[AK][FK])
create table p_i(
	idprato int,
	idingrediente int,
	primary key(idprato, idingrediente),
	foreign key(idprato) references pratos(idprato),
	foreign key(idingrediente) references ingredientes(idingrediente)
)

--Fornecedores(IDFornecedor[AK], Nome, Morada, Codigo_Postal, Pais)

create table fornecedores(
	idfornecedor int identity(1,1),
	nome varchar(128),
	morada varchar(256),
	codigo_postal varchar(56),
	pais varchar(56)
	primary key(idfornecedor)
)

--Enc(IDEncomendas[AK], IDFornecedor[AK][FK], IDIngrediente[AK][FK], Qtd, Data, Data_Entrega)
create table encomenda(
	idencomenda int identity(1,1),
	idfornecedor int,
	idingrediente int,
	qtd int,
	data datetime,
	data_entrega datetime,
	primary key(idencomenda, idfornecedor, idingrediente),
	foreign key(idfornecedor) references fornecedores(idfornecedor),
	foreign key(idingrediente) references ingredientes(idingrediente)
)

--Compras(Num_Factura[AK], IDFornecedor[AK][FK], IDIngrediente[AK][FK], Data, Qtd, Qtd_Actual, Data_Validade)
create table compras(
	num_factura int, --identity(1,1),
	idfornecedor int,
	idingrediente int,
	data datetime,
	qtd int,
	qtd_actual int,
	data_validade datetime,
	primary key(num_factura, idfornecedor, idingrediente),
	foreign key(idfornecedor) references fornecedores(idfornecedor),
	foreign key(idingrediente) references ingredientes(idingrediente)
)