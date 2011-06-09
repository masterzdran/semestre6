using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Author
{
  
    
        [Author("John", Given = "Smith")]
        [Author("Catia", Given = "Vaz")]
        [Author("AVE")]
        class Program
        {
            [Author("xpto")]
            class MyOne{}
            

            static void Main(string[] args)
            {
         


                Attribute[] attrs = Attribute.GetCustomAttributes(typeof(Program), typeof(AuthorAttribute));

                foreach (AuthorAttribute a in attrs)
                {
                    Console.WriteLine("{0} - {1}", a.Family, a.Given);
                }

                Console.WriteLine("*****************");

                Attribute[] att = Attribute.GetCustomAttributes(typeof(MyOne), typeof(AuthorAttribute));

                foreach (AuthorAttribute a in att)
                {
                    Console.WriteLine("{0} - {1}", a.Family, a.Given);
                }
             

            }



        }
    }

