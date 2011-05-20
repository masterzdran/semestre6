using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Aula05
{
    class Program
    {
        public static IEnumerable<T> Concat<T>(IEnumerable<T> seq1, IEnumerable<T> seq2)
        {
                foreach (T t in seq1)
                {
                    yield return t;
                }
                foreach (T t in seq2)
                {
                    yield return t;
                }
        }
        public static IEnumerable<int> betweenRange(int begin, int end)
        {
            for (; end >= begin; begin++)
            {
                yield return begin;
            }
        }
        public static bool isEven(int i)
        {
            return ((i & 1) == 0);
        }
        public static List<int> getEvens(List<int> list)
        {
            List<int> l = new List<int>();
            Predicate<int> p = new Predicate<int>(isEven);
            l = list.FindAll(p);
            return l;
        }
        
        public static void test1()
        {
            List<int> a = new List<int>();
            List<int> b = new List<int>();

            a.Add(1); a.Add(2); a.Add(3);
            b.Add(4); b.Add(5); b.Add(6);
            IEnumerable<int> i = Concat<int>(a, b);

            foreach (int j in i)
            {
                Console.WriteLine("[1] :::: {0}", j);

            }
        }
        public static void test2()
        {
            IEnumerable<int> i = betweenRange(1, 20);
            foreach (int j in i)
            {
                Console.WriteLine("[2] ::: {0}", j);
            }
        }
        public static void test3()
        {
            List<int> l = new List<int>();
            List<int> k = new List<int>();
            for (int i = 0; i < 20; ++i)
                l.Add(i);
            k = getEvens(l);
            foreach (int i in k)
            {
                Console.WriteLine("[3] ::: {0}", i);
            }

        }


        static public IEnumerable<T> Filter<T>(Predicate<T> predicate, IEnumerable<T> collection)
        {
            foreach (T item in collection)
                if (predicate(item))
                    yield return item;
        }
        static public IEnumerable<T> Transform<T>(Converter<T, T> transformer, IEnumerable<T> collection)
        {
            foreach (T item in collection)
                yield return transformer(item);
        }
        static public IEnumerable<U> Converter<T, U>(Converter<T, U> converter, IEnumerable<T> collection)
        {
            foreach (T item in collection)
                yield return converter(item);
        }
        //Considerando T tipo int e U tipo string: 

        static void show<U,T>(U i, IEnumerable<T> k)
        {
            foreach (T j in k)
            {
                Console.WriteLine("[{0}] ::: {1}",i, j);
            }
        }
        public static bool Filter(int i)
        {
            return ((i != 0) && ((i % 3) == 0));
        }
        public static String Converter(int a)
        {
            return "Testing:" + Transform(a); 
            
        }
        public static int Transform(int a)
        {
            return a * 2;           
        }


        static public void Filter_Test(List<int> l)
        {
            IEnumerable<int> k = Filter<int>(Filter, l);
            show(4, k);
        }
        static public void Transform_Test(List<int> l)
        {
            IEnumerable<int> k = Transform<int>(Transform, l);
            show(5, k);
        }
        static public void Converter_Test(List<int> l)
        {
            IEnumerable<String> k = Converter<int,String>(Converter, l);
            show(6, k);
        }

        static public IEnumerable<int> flip(IEnumerable<int> collection)
        {
            foreach (int i in collection)
            {
                if (Filter(i))
                {
                    yield return i;
                }
            }
        }


        static void allinOne(List<int> l)
        {
            IEnumerable<int> k = flip(l);
            IEnumerable<String> j = Converter<int, String>(Converter, k);
            show(7, j);
        }
        static void Main(string[] args)
        {
            List<int> l = new List<int>();
            for (int i = 0; i < 20; ++i)
                l.Add(i);

            test1();
            Console.WriteLine("-----------------------------------------------");
            test2();
            Console.WriteLine("-----------------------------------------------");
            test3();
            Console.WriteLine("-----------------------------------------------");
            
            Filter_Test(l);
            Console.WriteLine("-----------------------------------------------");
            Transform_Test(l);
            Console.WriteLine("-----------------------------------------------");
            Converter_Test(l);
            Console.WriteLine("-----------------------------------------------");
            allinOne(l);
            Console.WriteLine("-----------------------------------------------");
            Console.ReadLine();
        }
    }
}
