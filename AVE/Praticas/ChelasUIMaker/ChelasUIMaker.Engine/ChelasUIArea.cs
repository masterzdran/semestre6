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
        //private Delegate _action;
        public Control _control;
        //Corrected
        public ChelasUIArea(Action<T> action) // reordenado o código
        {
            T t = new T();
            // if (t == null) return; // é sempre falso pq tens ali uma restriçao
            if (action != null) action(t); // pode ou nao ser nulo. só aplicas a acçao uma vez, nao tens necessidade de a guardar

            //action(t);
            _control = t as Control;
            //_action = action;
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
                if (_control != null && t != null)
                {
                    _control.Controls.Add(t);
                }

            }
            //Não Gosto -> tambem nao, mas a outra soluçao muda-te muita coisa. tens de ter aqui uma XView e fazes _todo o código aqui dentro quase (pq tb te obriga a usar a ChelasUIView aqui)
            Config._control = _control;
            return this;
        }

        public override string ToString()
        {
            return String.Format("Name: ${0}", this.GetType().FullName);
        }
    }
    /*
    class ChelasUIArea<T> : IArea<T> where T : new() 
    {
        public Control _control;

        public ChelasUIArea(Action<T> action)
        {
            
            T t = new T();
            if (action != null) action(t);
            _control = t as Control;

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
     * */
}
