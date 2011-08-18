using System.Reflection;
using System.Windows.Forms;

namespace ChelasUIMaker.Engine
{
    using System;

    public abstract class Config
    {
        public static Control _graphics = new Control();
        public static Type _controller;

        public void Load()
        {
            _graphics.SuspendLayout();

            LoadConfig();

            _graphics.ResumeLayout();
        }

        protected abstract void LoadConfig();

        protected IArea<T> DefineArea<T>(Action<T> a) where T : new()
        {
            return new MyArea<T>(a);
        }

        private class MyArea<T> : IArea<T> where T : new()
        {
            public Control internalControl;

            public MyArea(Action<T> action)
            {
                T tmp = new T();
                if (action != null) action(tmp);
                internalControl = tmp as Control;

                if(internalControl==null)
                {
                    Console.WriteLine("o controlo é nulo");
                }
            }

            public IArea<T> WithController<C>()
            {
                _controller = typeof(C);

                return this;
            }

            public IArea<T> WithContent<U>(IArea<U> content)
            {
                var toAdd = content.GetType().GetField("internalControl").GetValue(content) as Control;

                
                if (internalControl != null && toAdd != null)
                {
                    internalControl.Controls.Add(toAdd);
                    //Console.WriteLine("added control = " + toAdd);
                }
                else
                {
                    Console.WriteLine("couldnt add control");
                }

                _graphics = internalControl;

                return this;
            }

            public override String ToString()
            {
                return "MyArea = " + internalControl;
            }
        }
    }
}