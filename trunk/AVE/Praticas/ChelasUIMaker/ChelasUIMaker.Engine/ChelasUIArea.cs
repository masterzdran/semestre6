using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Windows.Forms;

namespace ChelasUIMaker.Engine
{
    class ChelasUIArea<T> : IArea<T> where T : new() 
    {
        private Delegate _action;
        public Control _control;

        public ChelasUIArea(Action<T> action)
        {
            if (action == null) return;
            T t = new T();
            if (t == null) return;
            action(t);
            _control = t as Control;
            _action = action;
        }
        public IArea<T> WithController<C>()
        {
            //TODO: Validar o tipo;
            Config._controller = typeof(C);
           return this;
        }
        
        public IArea<T> WithContent<U>(IArea<U> content)
        {
            if (content != null)
            {
                var t = content.GetType().GetField("_control").GetValue(content) as Control;
                //var t = content as Control;
                if (_control != null && t  != null)
                {
                    _control.Controls.Add(t);
                }
                
            }
            //Não Gosto
            Config._control = _control;      
            return this;
        }
        public override string ToString()
        {
            return String.Format("Name: ${0}",this.GetType().FullName);
        }
    }
}
