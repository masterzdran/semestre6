using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Aluno3
{

     class Aluno
    {
        public int number;
        public String name;
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
                Type t = Type.GetType("Aluno3.Aluno");
                Console.WriteLine(t);
                MethodInfo m = t.GetMethod("GetName");
                //ListMethods(t);
                ListFields(t);
                Type list1 = Type.GetType("System.Collections.ArrayList");
                ListMethods(list1);
                Type list2 = Type.GetType("System.Collections.Generic.List`1");
                ListMethods(list2);
            }
            catch (Exception e) { Console.WriteLine(e); }

        }

        static void ListMethods(Type t)
        {
            Console.WriteLine("List Methods");
            MethodInfo[] mi = t.GetMethods();
            foreach (MethodInfo m in mi)
            {
                Console.WriteLine("-> {0}", m.Name);
            }
            Console.WriteLine();
        }

        static void ListFields(Type t)
        {
            Console.WriteLine("List Fields");
            FieldInfo[] fi = t.GetFields();
             foreach (FieldInfo f in fi)
            {
                Console.WriteLine("-> {0}", f.Name);
            }
            Console.WriteLine();
        }
        }

    }


