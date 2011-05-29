use SI2_TP1;
/*
Exercice 4 b.
Criar um evento gastronomico.
*/

if OBJECT_ID('CreateEvent') IS NOT NULL
	drop procedure CreateEvent;
go

create procedure CreateEvent(@CustomerID int, @MenuID int,@NameEvent char(20), 
				@Description char(20) , @date date, @Qtd int, @EventType tinyint)
as
	begin transaction
	--create a new event with the owner(customer)
		insert into dbo.BOOKING(CUSTOMER_ID, DATE,QTY,BOOKING_TYPE)
			values(@CustomerID, @date, @Qtd, @EventType);
		declare @BookingID int
		set @BookingID = 0
		select @BookingID = ID from BOOKING where
			(BOOKING.Customer_ID = @CustomerID AND BOOKING.Date = @date AND
				BOOKING.Qty = @Qtd)
		insert into event values(@BookingID, @MenuID, @NameEvent, @Description, @EventType);		

	--insert friends into guest table
	declare c cursor for select REGISTERED_ID2 from dbo.Friends where REGISTERED_ID1=@CustomerID
	open c
	declare @FriendID int
	fetch next from c into @FriendID
	while(@@FETCH_STATUS=0)
		begin
		insert into dbo.EVENT_FRIENDS(BOOKING_ID, CUSTOMER_ID, STATUS) values(@BookingID, @FriendID, 0)
		fetch next from c into @FriendID
		end
	close c
	deallocate c	
		
	commit