using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Testing8
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Reflection;
    using System.Text;
    using System.Diagnostics;

    namespace Reflector
    {
        class Program
        {


            public static void Reflect(object o)
            {
                Type t = o.GetType();

                Type b = t;
                do
                {
                    Console.Write("{0}->", b.FullName);
                    b = b.BaseType;
                } while (b != null);
                Console.WriteLine("\n----------------------------");

                MemberInfo[] members = t.GetMembers(BindingFlags.Public | BindingFlags.Instance | BindingFlags.Static);
                   
                    

                foreach (var member in members)
                {
                    Console.WriteLine("{0}", member.Name);
                }

                Console.WriteLine("****************");
                printing(members);
            }



            public static void printing(MemberInfo[] members)
            {
                var m=members.GroupBy(s => s.Name).
                Select(g => new { Name = g.Key, Count = g.Count() }).
                OrderByDescending(c => c.Count);

                foreach (var member in m)
                {
                    Console.WriteLine("{0} ({1})", member.Name, member.Count);
                }
            }

            static void Main(string[] args)
            {
                
                Reflect(1);
                

                

            }

        }
    }

}
