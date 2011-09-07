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
        private Control _control;
        private Type _controller;
        private T _type;

        public ChelasUIArea(Action<T> action)
        {
            _type = new T();
            if (action != null) action(_type);
            _control = _type as Control;
            
        }
        public IArea<T> WithController<C>()
        {
            _controller = typeof(C);
            return this;
        }

        public IArea<T> WithContent<U>(IArea<U> content)
        {
            if (content != null)
            {
                var c = content.Control();
                if (_control != null && c != null)
                {
                    _control.Controls.Add((Control)c);
                }
            }
            return this;
        }
        
        public Type Controller() {  return _controller;  }
        public Control Control() { return _control;  }
        
        public T Type() { return _type; }
        
        public override string ToString(){return String.Format("Name: ${0}", this.GetType().FullName);}
    }
    
}
