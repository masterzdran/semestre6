using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
//Pre-defined Attributes
namespace Aluno7
{
    [Serializable]
    class Aluno
    {
        public int number;
        public String name;
        [NonSerialized]
        public String nickName;
        public Aluno() { name = "AVE"; nickName = "Aluno_AVE";}
        public Aluno(int nr, String name) { number = nr; this.name = name; nickName = name + "_AVE"; }
        public String GetName() { return name; }
        public int GetNumber() { return number; }
        public void Print(String sep)
        {
            Console.WriteLine(sep +number);
            Console.WriteLine(sep +name);
            Console.WriteLine(sep +nickName);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            try{
            Aluno a=new Aluno();
            a.Print("-> ");
            FileStream fs = File.Open("data.dat", FileMode.Create);
            BinaryFormatter formatter = new BinaryFormatter();
            formatter.Serialize(fs, a);
            fs.Close();
            FileStream fs2 = File.Open("data.dat", FileMode.Open);
            BinaryFormatter form = new BinaryFormatter();
            Aluno b = (Aluno)form.Deserialize(fs2);
            b.Print("+> ");



            }
            catch (Exception e) { Console.WriteLine(e); }
            Console.Read();
        }
    }
}
