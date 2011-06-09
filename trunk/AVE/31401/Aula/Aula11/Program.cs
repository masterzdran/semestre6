using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Aula11
{
    class Program
    {
        static bool isCompatibleWithDelegate(Type t, MethodInfo mi)
        {
            return mi.GetType() == t;
        }

        delegate void x();

        static void ret()
        {

        }
        static void Main(string[] args)
        {
           // Console.WriteLine(">>> "+(isCompatibleWithDelegate(x,MethodInfo.GetCurrentMethod(ret))?"SIM":"NO"));
        }
    }
}
