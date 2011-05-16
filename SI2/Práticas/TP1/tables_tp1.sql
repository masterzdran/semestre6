use db_si_ap;

create table reuniao(
	data datetime,
	conclusao varchar(256)
	--constraint
)

create table comentario(
	idcomentario int identity(1,1),
	nota short check nota >= 1 && nota <= 5
	--constraint
)

create table r_com(
	datareuniao datetime,
	idcomentario int
	--constraint
)

create table cliente(
	idcliente int identity(1,1),
	nome varchar(128),
	contacto int
	--constraint
)

create table clienteregistado(
	idcliente int,
	endereco_postal varchar(56),
	nacionalidade varchar(56)
	--constraint
)

create table amigos(
	idcliente int,
	idamigo int
	--constraint
)

create table cli_com(
	idcliente int,
	idcomentario int,
)

create table ReservaNormal(
	idreserva int identity(1,1),
	data datetime,
	qtdpessoas int
)

create table ReservaEvento(
	idreserva int,
	organizador int,
	designacao varchar(128),
	descricao varchar(256)
)

create table cli_r(
	idreserva int,
	idcliente int
)

create table cardapio(
	idcardapio int identity(1,1),
	descricao varchar(256),
	categoria varchar(256)
)

create table r_car(
	idreserva int,
	idcardapio int	
)

create table pratos(
	idprato int identity(1,1),
	preco decimal(12,5),
	qtd smallint,
	activo bit
)

create table car_p(
	idcardapio int,
	idprato int
)

create table ingredientes(
	idingrediente int identity(1,1),
	nome varchar(128),
	descricao varchar(256),
	qtd_reserva int,
	qtd_actual int
)

create table p_i(
	idprato int,
	idingrediente int
)

create table fornecedores(
	idfornecedor int identity(1,1),
	nome varchar(128),
	morada varchar(256),
	codigo_postal varchar(56)
	pais varchar(56)
)

create table encomenda(
	idencomenda int identity(1,1),
	idfornecedor int,
	idingrediente int,
	qtd int,
	data datetime,
	data_entrega datetime
)

create table compras(
	num_factura int, --identity(1,1),
	idfornecedor int,
	idingrediente int,
	data datetime,
	qtd int,
	qtd_actual int,
	data_validade datetime
)