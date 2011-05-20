using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Aula07
{

    public static class ArrayUtils<T>
    {
        // public delegate void Action<T>(T obj);
        class Utils<T> where T : IComparable<T>
        {
            private T max;
            public Utils(T start)
            {
                max = start;
            }
            public void isGreat(T t)
            {
                if (max.CompareTo(t) < 0)
                    max = t;
            }
            public T Max
            {
                get { return max; }
            }

        }
        public static void Greatest<T>(T[] array) where T : IComparable<T>
        {
            T i = array[0];
            Utils<T> x = new Utils<T>(i);
            Action<T> action = new Action<T>(x.isGreat);
            Array.ForEach<T>(array, action);
            Console.WriteLine(":::\\> Max " + x.Max);
        }

    }

//----------------------------------------------------------------
   // public delegate TOutput Converter<TInput,TOutput> (TInput input);
   // public static U[] ConvertAll<T,U>(T[] array, Converter<T,U> converter);
    public struct Point
    {
        private int x;
        private int y;

        public Point(int xx)
        {
            x = 1;
            y = xx;
        }
        public override string ToString()
        {
            return String.Format("({0},{1})",x,y);
        }
    }

/*
    class Program
    {
        public static IEnumerable<KeyValuePair<K, U>> Mapper<T, K, U>(this IEnumerable<T> input,Func<T, IEnumerable<KeyValuePair<K, U>>> map)
        {
            return null;
            
        }
        public static IEnumerable<KeyValuePair<string, int>> CountWords(IEnumerable<string> lines)
        {
            return null;
        } 


        static void Main(string[] args)
        {
            string[] lines = { "ola mundo ola ave", "ave ola ave" };
            foreach (KeyValuePair<string, int> p in CountWords(lines))
                Console.WriteLine(p); 
        }
    }
 * */
/*
    class Program
    {

        static void question3()
        {
            char[] x = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
            ArrayUtils<char>.Greatest<char>(x);
            Console.ReadLine();
        }

        static void Main(string[] args)
        {

        }
    }
 * */

    public class Program
    {
        public static Point MyConverter(int x)
        {
            return new Point(x);
        }

        public static Point[] ConvertingPoints(int[] array)
        {
            return Array.ConvertAll<int, Point>(array, MyConverter);
        }

        static void question4()
        {
            int[] values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            Point[] newValues = ConvertingPoints(values);
            foreach (Point j in newValues)
                Console.WriteLine(j);
            Console.ReadLine();

        }

        public static void Main()
        {
            Console.ReadLine();
        }
    }

}
