using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Testes
{
    class Program
    {
        struct S
        {
            public int x;
            public S(int y)
            {
                x = y;
            }

            public ~S()
            {
                x = 1;
            }
        }
        static void Main(string[] args)
        {
            S s = new S();
            Console.WriteLine(s.x);
            Console.ReadLine();
            
        }
    }
}
