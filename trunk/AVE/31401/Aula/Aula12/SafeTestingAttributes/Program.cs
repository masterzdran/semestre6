using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SafeTestingAttributes
{

    interface IAlarm { event EventHandler trigger;}
    public class AlarmProcessor1
    {
        public void onAlarm(object src, EventArgs arg)
        {
        Console.WriteLine("AlarmProcessor1 OnAlarm");
        }
    }

    public class AlarmProcessor2
    {
        public void onAlarm(object src, EventArgs arg)
        {
            Console.WriteLine("AlarmProcessor2 OnAlarm");
        }
    }


    class UnfriendTypeException : Exception
    {
        private Type unfriend;
        public UnfriendTypeException(Type t)
        {
            unfriend = t;
        }

        public override string ToString()
        {

            return base.ToString() + "UnfriendType: " + unfriend + "\n";
        }

    }

    [FriendType(typeof(SafeTestingAttributes.AlarmProcessor1))]
    public class AlarmGenerator : IAlarm
    {

        private event EventHandler myTrigger;

        public event EventHandler trigger
        {
            add
            {
                Console.WriteLine("Adding...  " + value.Target.GetType());
                if (!Program.isSafeCallback(this.GetType(), value)) 
                    throw new UnfriendTypeException(value.Target.GetType());
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
           //Os métodos são estáticos, logo não posso 
            Object o = d.Target;

            Type tt = o.GetType();
            Type myType = Type.GetType("SafeTestingAttributes.FriendTypeAttribute");
            SafeTestingAttributes.FriendTypeAttribute[] atributes;
          
            atributes= (SafeTestingAttributes.FriendTypeAttribute[])t.GetCustomAttributes(myType, false);
          
            for (int i = 0; i < atributes.Length; i++)
            {
     
                
                if(atributes[i].Value.Equals(tt)) return true;
                
            }
            return false;
        }




        static void Main(string[] args)
        {
            AlarmGenerator a = new AlarmGenerator();
        /*   a.trigger += AlarmProcessor1.onAlarm;
            a.trigger += AlarmProcessor1.onAlarm;
            a.trigger += AlarmProcessor2.onAlarm;*/
           AlarmProcessor1 a1 = new AlarmProcessor1();
            AlarmProcessor2 a2 = new AlarmProcessor2();
            a.trigger += a1.onAlarm;
            a.trigger += a1.onAlarm;
             a.trigger += a2.onAlarm;
             a.Generate();
        }

        
    }
}
