use SI2_TP1
/*Ex4 - k)
	Apresentar os cardápios que dão mais lucro.
*/
if OBJECT_ID('MostProfitMenu') IS NOT NULL
	drop function MostProfitMenu;
go	

create function MostProfitMenu()
returns @MostSales table(
			NAME_MENU			varchar(30),
			PROFIT			smallmoney)
as
	begin TRANSACTION ISOLATION LEVEL READ COMMITTED
		insert into @MostSales
				select MENU.NAME, SUM(SALE_PRICE - COST_PRICE) as DIF
	from BOOKING inner join NORMAL_BOOKING on BOOKING.ID = NORMAL_BOOKING.BOOKING_ID
				 inner join MENU on NORMAL_BOOKING.MENU_ID = MENU.ID
	GROUP BY MENU.NAME
	ORDER BY DIF desc
		
	return
	end
