using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Author
{
  
    
        [Author("John", Given = "Smith")]
        [Author("Catia", Given = "Vaz")]
        [Author("AVE")]
        [Serializable]
        class MyClass
        {
        }
            
        class Program{
            static void Main(string[] args)
            {

                ReflectOnAtributes1();
                Console.WriteLine("*******");
                Assembly b = Assembly.Load("Reflection");
                Console.WriteLine("######################");
                // GetExportedTypes(b);
                // DisplayTypesInAsm(b);
    
                ReflectOnAtributes2(b);
                ReflectOnAtributes2(Assembly.GetExecutingAssembly());

              
        
            }


            private static void ReflectOnAtributes1(){
                Type t=typeof(MyClass);
                object[] atrib=t.GetCustomAttributes(false);
                foreach (Attribute a in atrib)
                    Console.WriteLine(a.ToString());
            }

            private static void ReflectOnAtributes2(Assembly b)
            {

                Type[] types = b.GetTypes();
                foreach (Type t in types)
                {
                    object[] atrib = t.GetCustomAttributes(false);
                    foreach (Attribute a in atrib)
                    {
                        Console.WriteLine("->{0}:{1}\n", t.Name, a.ToString());
                    }

                }

            }
        }
    }

