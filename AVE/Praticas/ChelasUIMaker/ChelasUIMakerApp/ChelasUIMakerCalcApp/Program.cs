using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ChelasUIMaker.Engine;


namespace ChelasUIMakerCalcApp
{
    class Program
    {
        static void Main(string[] args)
        {
            XView xv = ViewEngine.LoadConfig(new MyCalcConfig());
            Application.Run(xv.Control);
        }
    }
}
