using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
namespace Aluno2
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
                Type myTypeObj = Type.GetType("Aluno2.Aluno");
                object a2 = Activator.CreateInstance(myTypeObj);
                Type t = a2.GetType();
                Console.WriteLine(t);
                MethodInfo m = t.GetMethod("GetName");
                String s = (String)m.Invoke(a2, null);
                Console.WriteLine(s);
                object a3 = Activator.CreateInstance(myTypeObj, new object[2] { 3, "Alice" });
                String ss = (String)a3.GetType().GetMethod("GetName").Invoke(a3, null);
                Console.WriteLine(ss);
              
            }
            catch (Exception e) { Console.WriteLine(e); }

        }

      
    }
}
