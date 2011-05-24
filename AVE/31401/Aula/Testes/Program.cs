using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Testes
{
    class Program
    {

        static void Main(string[] args)
        {
            int[] source = new[] { 3, 8, 4, 6, 1, 7, 9, 2, 4, 8 };

            foreach (int i in source.Where(x => x > 5))
                Console.WriteLine(i);

            Console.Read();
        }
    }
}
