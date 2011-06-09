using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace ReflectionUtils
{
    class DelegateUtils
    {
        /*
         que recebe como parâmetros o objecto o e representante t de um tipo delegate, 
         retorna um array com os representantes dos métodos de o que são compatíveis 
         com o tipo delegate representado por t.
         */
        public static MethodInfo[] GetCompatibleMethods(object o, Type t)
        {
            return null;
        }
    }
    
    class Program
    {
        /*
          o qual verifica se o tipo representado por t implementa a interface representada por tIntf. 
         */
        static bool ImplementsInterface(Type t, Type tIntf)
        {
            Type[] type = t.GetInterfaces();
            foreach (Type myType in type)
                if (myType.Equals(tIntf)) return true;
            return false;
        }
        /*
         o qual verifica se o tipo representado por t implementa o padrão Disposable, isto é, 
         se contém todos os métodos necessários à concretização deste padrão
         */
        static bool IsDisposablePattern(Type t)
        {
            MethodInfo[] method = t.GetMethods();
            foreach (MethodInfo m in method)
            {
                //Verify Method Name
                if (m.Name.Equals("Dispose"))
                {   
                    //Verify Return Type
                    if (!m.ReturnType.Equals("VOID")){ return false;}
                    ParameterInfo[] p = m.GetParameters();
                    //Verify Arguments
                    if (p.Length != 0) { return false; }
                }
            }
            return true;
        }

        /*
         que determina se o objecto o corresponde à versão boxed de uma instância de tipo valor. 
         */
        static bool isBoxedInstance(object o)
        {
            return (o.GetType()).IsValueType; 
        }

        /*
         que retorna true se o método mi tiver uma assinatura compatível com o tipo delegate representado por t.  
         */
        static bool isCompatibleWithDelegate(Type t, MethodInfo mi)
        {

            
            return false;
        }


        static void Main(string[] args)
        {
            ArrayList a=new ArrayList();
            IList b = (IList)a;
            Console.WriteLine(a);
            Console.WriteLine(Type.GetType("System.Collections.IList"));
           Console.WriteLine( ImplementsInterface(a.GetType(), Type.GetType("System.Collections.IList")));
           Console.WriteLine("------");
           Console.WriteLine("The object is :" + ((isBoxedInstance(b))?"value":"reference" )+ " type");
           Console.ReadLine();
        }
    }
}
