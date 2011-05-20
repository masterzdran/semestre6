using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Aula08
{
    class Stock
    {
        private Double price;
        public event EventHandler<StockPriceChangeEventArgs> priceChanged;

        public Stock(Double p)
        {
            price = p;
        }

        public Double Price
        {
            get{return price;}
            set
            {
                StockPriceChangeEventArgs args = new StockPriceChangeEventArgs(price, value);
                price=value;
                OnPriceChanged(args);
            }
        }
        virtual protected void OnPriceChanged(StockPriceChangeEventArgs args) 
        {
            if (priceChanged != null)
            {
                priceChanged(this,args);
            }
        }
    }

    class StockPriceChangeEventArgs : System.EventArgs
    {
        private double _oldPrice;
        private double _newPrice;

        public StockPriceChangeEventArgs(double old_price, double new_price)
        {
            _oldPrice = old_price;
            _newPrice = new_price;
        }
        public Double OldPrice { get { return _oldPrice; } }
        public Double NewPrice { get { return _newPrice; } }

    }

    class StockPriceObserver
    {
        public StockPriceObserver(Stock s)
        {
            s.priceChanged += this.PriceChanged;
        }
        public void PriceChanged(Object sender, StockPriceChangeEventArgs tmp)
        {
            Console.WriteLine("Stock Observer: OLD = {0} , NEW = {1} , CHANGE =  {2}", tmp.OldPrice, tmp.NewPrice, tmp.NewPrice-tmp.OldPrice);
        }
    }

    class BrokerStockPriceObserver
    {
        public BrokerStockPriceObserver(Stock s)
        {
            s.priceChanged += this.PriceChanged;
        }
        public void PriceChanged(Object sender, StockPriceChangeEventArgs tmp)
        {
            if (tmp.NewPrice - tmp.OldPrice > 10)
                Console.WriteLine("Broker Stock Observer: OLD = {0} , NEW = {1} , CHANGE =  {2}", tmp.OldPrice, tmp.NewPrice, tmp.NewPrice - tmp.OldPrice);
        }
    }

    //Done Temperature
    class StockPrice_RX
    {
        private double _oldPrice;
        private double _newPrice;
        public StockPrice_RX(double old_price, double new_price)
        {
            _oldPrice = old_price;
            _newPrice = new_price;
        }
        public Double OldPrice { get { return _oldPrice; } }
        public Double NewPrice { get { return _newPrice; } }
    }

    //DONE Thermostat
    class Stock_RX : IObservable<StockPrice_RX>
    {
        private Double price;
        private List<IObserver<StockPrice_RX>> observers;

        public Stock_RX(Double p)
        {
            price = p;
            observers = new List<IObserver<StockPrice_RX>>();
        }

        public IDisposable Subscribe(IObserver<StockPrice_RX> observer)
        {
            if (! observers.Contains(observer))     observers.Add(observer); 
            return new Unsubscriber(observers, observer);
        }
        private class Unsubscriber : IDisposable
        {
            private List<IObserver<StockPrice_RX>> _observers;
            private IObserver<StockPrice_RX> _observer;
            public Unsubscriber(List<IObserver<StockPrice_RX>> observers, IObserver<StockPrice_RX> observer)
            {
                _observers = observers;
                _observer = observer;
            }
            public void Dispose()
            {
                if (_observer != null && _observers.Contains(_observer))
                    _observers.Remove(_observer);
            }
        }
                
        public Double Price
        {
            get { return price; }
            set
            {
                StockPrice_RX s = new StockPrice_RX(price, value);
                price = value;
                foreach (var observer in observers) { observer.OnNext(s); }
            }
        }
    }

    
    class StockPriceObserver_RX : IObserver <StockPrice_RX>
    {
        private IDisposable unsubs;
        public virtual void Subscribe(IObservable<StockPrice_RX> provider)
        {
            if (provider != null) unsubs = provider.Subscribe(this);
        }
        public virtual void OnCompleted() 
        {
            Console.WriteLine("StockPriceObserver_RX:ChangeObserver:Completed");
            this.Unsubscribe(); 
        }
        public virtual void OnError(Exception e) { Console.WriteLine("StockPriceObserver_RX:ChangeObserver:Can not be completed"); }
        public virtual void OnNext(StockPrice_RX value) {
            Console.WriteLine("StockPriceObserver_RX:ChangeObserver: Old={0}, New={1}, Changed={2}",
               value.OldPrice, value.NewPrice,
               value.NewPrice - value.OldPrice);
        }
        public virtual void Unsubscribe() { unsubs.Dispose(); }
        
    }

    class BrokerStockPriceObserver_RX : IObserver<StockPrice_RX>
    {
        private IDisposable unsubs;
        public virtual void Subscribe(IObservable<StockPrice_RX> provider)
        {
            if (provider != null) unsubs = provider.Subscribe(this);
        }
        public virtual void OnCompleted()
        {
            Console.WriteLine("BrokerStockPriceObserver_RX:ChangeObserver:Completed");
            this.Unsubscribe();
        }
        public virtual void OnError(Exception e) { Console.WriteLine("BrokerStockPriceObserver_RX:ChangeObserver:Can not be completed"); }
        public virtual void OnNext(StockPrice_RX value)
        {
            if (value.NewPrice - value.OldPrice > 10 )
                Console.WriteLine("BrokerStockPriceObserver_RX: Old={0}, New={1}, Changed={2}",
               value.OldPrice, value.NewPrice,
               value.NewPrice - value.OldPrice);
        }
        public virtual void Unsubscribe() { unsubs.Dispose(); }
    } 


    
    class Program
    {
        public static void _via_Eventos()
        {
            Stock s1 = new Stock(10);
            StockPriceObserver so = new StockPriceObserver(s1);
            BrokerStockPriceObserver bo = new BrokerStockPriceObserver(s1);

            for (int i = 1; i < 1000; i += i % 17)
            {
                s1.Price = i;
            }
        }

        public static void _via_RX()
        {
            Stock_RX s1 = new Stock_RX(10);
            StockPriceObserver_RX so = new StockPriceObserver_RX();
            BrokerStockPriceObserver_RX bo = new BrokerStockPriceObserver_RX();
            s1.Subscribe(so);
            s1.Subscribe(bo);

            for (int i = 1; i < 1000; i += i % 17)
            {
                s1.Price = i;
            }
        }
        static void Main(string[] args)
        {
            //_via_Eventos();
            _via_RX();
            Console.ReadLine();
        }
    }
}
