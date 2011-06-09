using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Aluno6
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                String dataAssembly = "System.Data, version=4.0.0.0, " + "culture=neutral, PublicKeyToken=b77a5c561934e089";
                Assembly a = Assembly.Load(dataAssembly);
              //  GetExportedTypes(a);
               // DisplayTypesInAsm(a);
                LoadedFrom(a);
                //Consegue encontrar porque está em debug/bin
                Assembly b = Assembly.Load("Reflection");
                Console.WriteLine("######################");
               // GetExportedTypes(b);
               // DisplayTypesInAsm(b);
                LoadedFrom(b);
     }
            catch (Exception e) { Console.WriteLine(e); }
        }

        static void LoadedFrom(Assembly asm)
        {
            Console.WriteLine("Loaded from GAC? {0}", asm.GlobalAssemblyCache);
        }

        static void DisplayTypesInAsm(Assembly asm)
        {
            Console.WriteLine("*********Types in Assembly**********");
            Console.WriteLine("->{0}", asm.FullName);
            Type[] types = asm.GetTypes();
            foreach (Type t in types)
                Console.WriteLine("Type: {0}", t);
        }


        static void GetExportedTypes(Assembly x){
             foreach (Type t in x.GetExportedTypes()) 
                 Console.WriteLine(t.FullName);
      }


    }
}
