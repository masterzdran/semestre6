using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;


namespace MethodTestingAttributes
{
    class Program
    {
        //b)
        public static bool IsMethodToTest(MethodInfo mi)
        {
            Type t = Type.GetType("MethodTestingAttributes.MethodTestAttribute");
            object[] atrib = mi.GetCustomAttributes(t, false);
            if (atrib.Length != 1) return false;
            return (mi.GetParameters().Length == 0 &&
                    (! mi.ReturnType.Equals(Type.GetType("System.Void"))) &&
                    (! mi.ReturnType.IsArray) &&
                    (! mi.ReturnType.BaseType.Equals(Type.GetType("System.MulticastDelegate")))
                );
        }

        public delegate void X();

        [MethodTest("OLA1")]
        public static bool xpto1(){ return true; }

        [MethodTest("OLA2")]
        public static void xpto2(){ }

        [MethodTest("OLA3")]
        public static void xpto3(string s) { }

        [MethodTest("OLA4")]
        public static X xpto4(int x) { return null; }
        [MethodTest("OLA5")]
        public static int[] xpto5() { return null; }

        static void Main(string[] args)
        {
            Console.WriteLine("*****b)**********");
            Type tt = Type.GetType("MethodTestingAttributes.Program");
            Console.WriteLine(IsMethodToTest(tt.GetMethod("xpto1")));
            Console.WriteLine(IsMethodToTest(tt.GetMethod("xpto2")));
            Console.WriteLine(IsMethodToTest(tt.GetMethod("xpto3")));
            Console.WriteLine(IsMethodToTest(tt.GetMethod("xpto4")));
            Console.WriteLine(IsMethodToTest(tt.GetMethod("xpto5")));
            Console.WriteLine("*******c)**********");
             Pair<MethodInfo, bool>[] testing = testAllMethods(new TestClass());
            foreach (Pair<MethodInfo, bool> p in testing)
            {
                Console.WriteLine(p.MyT);
                Console.WriteLine(p.MyW);
            }
        }

        //d)
        public static Pair<MethodInfo, bool>[] testAllMethods(Object obj)
        {
            Type t = obj.GetType() ;
            MethodInfo[] methods = t.GetMethods();
            Pair<MethodInfo, bool>[] toReturn = new Pair<MethodInfo, bool>[methods.Length];
            int index = 0;
            for (int i = 0; i < methods.Length; i++)
            {
                MethodInfo m = methods[i];
                if (IsMethodToTest(m))
                {
                    object a = m.Invoke(obj, null);
                    Type tt = Type.GetType("MethodTestingAttributes.MethodTestAttribute");
                    object[] o = m.GetCustomAttributes(tt, false);
                    Pair<MethodInfo, bool> p = new Pair<MethodInfo, bool>();
                    p.MyT = m;
                    MethodTestAttribute mt = (MethodTestAttribute)o[0];
                    if (mt.Value.ToString().Equals(a.ToString())) 
                    {
                        p.MyW = true;
                    }
                    else
                    {
                        p.MyW = false;
                    }
                    toReturn[index++] = p;
                }
            }
            Pair<MethodInfo, bool>[] toReturn2 = new Pair<MethodInfo, bool>[index];
            Array.Copy(toReturn, 0, toReturn2,0,index);
            return toReturn2;
        }
    }
}
