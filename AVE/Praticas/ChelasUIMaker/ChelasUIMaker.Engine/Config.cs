namespace ChelasUIMaker.Engine
{
    using System;
    using System.Reflection;
    using System.Windows.Forms;
    

    public abstract class Config 
    {
        Object _area;
        Type _parameter;

        public void Load()
        {
            LoadConfig();
        }

        protected abstract void LoadConfig();
        
        protected IArea<T> DefineArea<T>(Action<T> a) where T : new()
        {
            IArea<T> area = new ChelasUIArea<T>(a);

            _area = area;
            _parameter = typeof(T);
            return area;
        }

        public Object IArea { get { return _area; } }
        public Type ParameterType { get { return _parameter; } }


    }

}