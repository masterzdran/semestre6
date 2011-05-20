using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Aula06
{
    public delegate string Formatter();

    public sealed class Logger
    {
        int currLevel;
        //Invocações do método Log que especificam um nível (level) inferior ao nível corrente são descartadas, 
        //não se fazendo nenhum registo das mesmas.
        public void Log(int level, Formatter msg)
        {
            if (level >= currLevel)
                dispatch(msg);
        }

        // faz log da mensagem msg 
        protected void dispatch(Formatter msg)
        {
            Console.WriteLine(msg());
        }

        //A propriedade level permite obter/alterar o nível corrente do logger. 
        public int Level
        {
            set { currLevel = value; }
            get { return currLevel; }
        }
    }
    class Program
    {

        private static long v1;
        private static String v2;
        private static int en;
        /**
         *  No método UseLogger, apresentado , a construção da string msg é trabalho perdido se log 
            tiver um nível corrente superior a 5, uma vez que a mensagem é descartada. De forma a evitar esta situação
            criou-se o tipo delegate string Formatter() com o objectivo de invocar o código de construção da string 
            apenas quando for estritamente necessário. Modifique o método Log para passar a receber uma instância do 
            tipo Formatter e altere o método UseLogger para invocar a nova versão do método Log.       
         */
        public static void UseLogger(Logger log, long val1, string val2, int errNumber)
        {

            en = errNumber; v1 = val1; v2 = val2;
            log.Log(5, formatStr);
        }

        public static String formatStr()
        {
            return String.Format("Ocorreu o erro {0}  com os valores({1}, {2})", en, v1, v2);
        }
        public static void Main2()
        {
            Logger l = new Logger();
            l.Level = 2;
            UseLogger(l, 2, "xpto", 2);
            l.Level = 6;
            UseLogger(l, 6, "xpto", 6);
            Console.Read();
        }
    }
     public delegate int Comparison<T>(T x, T y);
    class Sorter
    {
        public static void mySort<T>(IList<T> l, Comparison<T> cmp) //alteração da assinatura
        {
            for (int i = 0; i < l.Count - 1; i++)
            {
                for (int j = i + 1; j < l.Count; j++)
                {
                    if (cmp(l[i], l[j]) > 0)            //unica alteração efectuada
                    {
                        T aux = l[j];
                        l[j] = l[i];
                        l[i] = aux;
                    }
                }
            }
        
        }
        
        public static void Sort<T>(IList<T> l, IComparer<T> cmp)
        {
            for (int i = 0; i < l.Count-1; i++)
            {
                for (int j = i + 1; j < l.Count; j++)
                {
                    if (cmp.Compare(l[i], l[j]) > 0)
                    {
                        T aux = l[j];
                        l[j] = l[i];
                        l[i] = aux;
                    }
                }
            }
        }
    }
    class App{  
        static void printElements(short[] a) 
        {
            foreach(short i in a){
                Console.Write(i+",");
            }
            Console.Write("\b \n");
        }  

        static void Main(){  
         short[] dummy = {3,4,6,2,1,8,5,9,6,7,0};
         short[] dummy2 = { 3, 4, 6, 2, 1, 8, 5, 9, 6, 7, 0 }; 
         printElements(dummy);
         printElements(dummy2);
         Console.WriteLine();
         Sorter.Sort(dummy, new Int16Comparer());  
         printElements(dummy);
         printElements(dummy2);
         Console.WriteLine();
         Sorter.mySort(dummy2, new Int16Comparer().Compare);
         printElements(dummy2);
         Console.ReadLine();
       }  
        class Int16Comparer:IComparer<short>{  public int Compare(short n1, short n2){  return (int) n1-n2; }   }  
    } 
}
