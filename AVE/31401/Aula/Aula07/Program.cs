using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Aula07
{

    public static class ArrayUtils
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
            return String.Format("({0},{1})", x, y);
        }
    }



    class question3
    {

        static void q3()
        {
            char[] x = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
            //ArrayUtils<char>.Greatest<char>(x);
            Console.ReadLine();
        }
    }

    public class question4
    {

        public static Point MyConverter(int x)
        {
            return new Point(x);
        }

        public static Point[] ConvertingPoints(int[] array)
        {
            return Array.ConvertAll<int, Point>(array, MyConverter);
        }

        static void q4()
        {
            int[] values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            Point[] newValues = ConvertingPoints(values);
            foreach (Point j in newValues)
                Console.WriteLine(j);
            Console.ReadLine();

        }

    }
    public static class question5
    {
        public static IEnumerable<KeyValuePair<K, U>> Mapper<T, K, U>(this IEnumerable<T> input, Func<T, IEnumerable<KeyValuePair<K, U>>> map)
        {
            return input.SelectMany(map);
        }

        public static IEnumerable<KeyValuePair<string, int>> CountWords(IEnumerable<string> lines)
        {
            return Mapper(lines,
                delegate(String input)
                {
                    Dictionary<String, int> d = new Dictionary<String, int>();
                    String[] i = input.Split(' ');

                    foreach (String s in i)
                    {
                        if (d.ContainsKey(s))
                            d[s]++;
                        else
                            d.Add(s, 1);
                    }
                    return d;
                }
            );
        }

    }
    public static class question6
    {
        public static IEnumerable<KeyValuePair<K, U>> Mapper<T, K, U>(this IEnumerable<T> input, Func<T, IEnumerable<KeyValuePair<K, U>>> map)
        {
            return question5.Mapper(input, map);
        }

        public static IEnumerable<IGrouping<K, KeyValuePair<K, U>>> Joiner<K, U>(this IEnumerable<KeyValuePair<K, U>> input) where K : IComparable<K>
        {
            return input.GroupBy(x => x.Key);
        }

        public static IEnumerable<KeyValuePair<K, V>> Reducer<K, U, V>(this IEnumerable<IGrouping<K, KeyValuePair<K, U>>> groups, Func<IGrouping<K, KeyValuePair<K, U>>, KeyValuePair<K, V>> reduce)
        {
            return groups.Select(reduce);
        }

        public static IEnumerable<KeyValuePair<string, int>> CountWords(IEnumerable<string> lines)
        {
            return Reducer(Joiner(question5.CountWords(lines)), x =>
            {
                KeyValuePair<string, int> par = new KeyValuePair<string, int>("", 0);

                foreach (KeyValuePair<string, int> p in x)
                {
                    par = new KeyValuePair<string, int>(p.Key, p.Value + par.Value);
                }
                return par;



            });
        }
    }

    class Program
    {

        public static void q5()
        {
            string[] lines = { "ola mundo ola ave", "ave ola ave" };
            foreach (KeyValuePair<string, int> p in question5.CountWords(lines))
                Console.WriteLine(p);
        }
        public static void q6()
        {
            string[] lines = { "ola mundo ola ave", "ave ola ave" };
            foreach (KeyValuePair<string, int> p in question6.CountWords(lines))
                Console.WriteLine(p);
        }

        public static void Main()
        {
            q6();
            Console.ReadLine();
        }
    }






}
