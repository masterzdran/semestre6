using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Aluno4
{
    class Aluno
    {
        public int number;
        public String name;
        public static int nAlunos;
        private int xpto;
        private static int x;
        public Aluno() { name = "AVE"; }
        public Aluno(int nr, String name) { number = nr; this.name = name; }
        public String GetName() { return name; }
        public int GetNumber() { return number; }
    }
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Type t = Type.GetType("Aluno4.Aluno");
                Console.WriteLine(t);
                const BindingFlags binding1 = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance;
                ListFields(t,binding1);
                Console.WriteLine("**********************");
                const BindingFlags binding2 = BindingFlags.Static | BindingFlags.Instance;
                ListFields(t, binding2);
                const BindingFlags binding3 = BindingFlags.Public | BindingFlags.Static | BindingFlags.Instance;
                ListFields(t, binding3);
                const BindingFlags binding4 = BindingFlags.Public | BindingFlags.NonPublic| BindingFlags.Static | BindingFlags.Instance;
                ListFields(t, binding4);
                const BindingFlags binding5 = BindingFlags.Public | BindingFlags.NonPublic;
                ListFields(t, binding5);


            }
            catch (Exception e) { Console.WriteLine(e); }
        }
             static void ListFields(Type t, BindingFlags b)
        {
            Console.WriteLine("List Methods");
            FieldInfo[] mi = t.GetFields(b);
            foreach (FieldInfo m in mi)
            {
                Console.WriteLine("-> {0}", m.Name);
            }
            Console.WriteLine();
        }

        }

    }

