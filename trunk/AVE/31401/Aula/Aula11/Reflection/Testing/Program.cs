using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Testing
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                //With reflection
                Assembly ass=Assembly.LoadFrom(@"D:\work\AVE2011\ExerciciosCSharp\Reflection\Reflection\bin\Debug\Reflection.exe");
                Type myTypeObj = ass.GetType("Alunos.Aluno");

                //Type myTypeObj = Type.GetType("Alunos.Aluno");
                object a2 = Activator.CreateInstance(myTypeObj);
                Type t = a2.GetType();
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
