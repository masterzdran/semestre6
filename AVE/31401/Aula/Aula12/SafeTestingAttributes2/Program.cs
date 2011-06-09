using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace SafeTestingAttributes2
{
        interface IAlarm { event EventHandler trigger;}
        public class AlarmProcessor1
        {
            public static void onAlarm(object src, EventArgs arg)
            {
                Console.WriteLine("AlarmProcessor1 OnAlarm");
            }
        }

        public class AlarmProcessor2
        {
            public static void onAlarm(object src, EventArgs arg)
            {
                Console.WriteLine("AlarmProcessor2 OnAlarm");
            }
        }


        class UnfriendTypeException : Exception
        {
            private Type unfriend;
            public UnfriendTypeException(Type t){ unfriend = t; }

            public override string ToString()
            {
                return base.ToString() + "UnfriendType: " + unfriend + "\n";
            }

        }

        [FriendType2(typeof(SafeTestingAttributes2.AlarmProcessor1))]
        public class AlarmGenerator : IAlarm
        {

            private event EventHandler myTrigger;

            public event EventHandler trigger
            {
                add
                {
                    Console.WriteLine("Adding...  " + value.Method.DeclaringType);
                    if (!Program.isSafeCallback(this.GetType(), value))
                        throw new UnfriendTypeException(value.Method.DeclaringType);
                    myTrigger += value;
                }
                remove
                {
                    myTrigger -= value;
                }
            }

            public void Generate()
            {
                myTrigger.Invoke(this, EventArgs.Empty);
            }


        }




        class Program
        {

            public static bool isSafeCallback(Type t, Delegate d)
            {
                 // Método associado ao Delegate
                  MethodInfo method = d.Method;
                 // Tipo onde o método (static ou de instância) está definido
                 Type tt = method.DeclaringType;
                 Type myType = Type.GetType(" SafeTestingAttributes2.FriendType2Attribute");
                 foreach (SafeTestingAttributes2.FriendType2Attribute att in t.GetCustomAttributes(myType, false))
                 {
                    if ( att.Value!=null && att.Value.Equals(tt)) return true;

                 }
                 return false;
            }


            static void Main(string[] args)
            {
                AlarmGenerator a = new AlarmGenerator();
                a.trigger += AlarmProcessor1.onAlarm;
                a.trigger += AlarmProcessor1.onAlarm;
                //  a.trigger += AlarmProcessor2.onAlarm;
                a.Generate();
            }


        }
    }

