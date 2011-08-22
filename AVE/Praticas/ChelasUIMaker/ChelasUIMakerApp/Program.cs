using System;
using ChelasUIMaker.Engine;
using System.Windows.Forms;

namespace ChelasUIMakerApp
{
    

    class Program
    {
        static void Main(string[] args)
        {

            XView xv = ViewEngine.LoadConfig(new MyConfig());
            Application.Run((Form)xv.Control);
        }
    }
}
