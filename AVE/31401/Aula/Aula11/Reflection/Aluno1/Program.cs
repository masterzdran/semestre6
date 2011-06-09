using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Aluno1
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
             try{
			   Type myTypeObj = Type.GetType("Aluno1.Aluno");
			   object a2 = Activator.CreateInstance(myTypeObj);
			   Type t=a2.GetType();
			   Console.WriteLine(t);
			}
			catch(Exception e){Console.WriteLine(e);}

        }
        }
    }

