using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CollectionClasses1
{
    class Program
    {
        public static void Main()
        {
                Tokens f = new Tokens("This is a well-done program.",  new char[] {' ','-'});
                foreach (string item in f)
                {
                   Console.WriteLine(item);
                }
            
            Token1 ff = new Token1("This is a well-done program.", new char[] { ' ', '-' });
            foreach (string item in ff)
            {
                Console.WriteLine(item);
            }

            IEnumerator i = f.GetEnumerator();
            i.Reset();
            Console.WriteLine(i.MoveNext());
            Console.WriteLine(i.Current);

      
            IEnumerator ii=ff.GetEnumerator();
            ii.Reset();
            Console.WriteLine(ii.MoveNext());
            Console.WriteLine(ii.Current);
            Console.WriteLine(ii.MoveNext());
            Console.WriteLine(ii.Current);
        }


        }

    }

