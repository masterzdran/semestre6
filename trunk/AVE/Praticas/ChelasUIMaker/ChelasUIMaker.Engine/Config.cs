namespace ChelasUIMaker.Engine
{
    using System;
    using System.Reflection;
    using System.Windows.Forms;

    public abstract class Config 
    {
        readonly String _dataAssembly = "System.Windows.Forms,version=4.0.0.0,Culture=neutral,PublicKeyToken=b77a5c561934e089";
        Assembly _assembly;
        Type[] _types;
        //Não Gosto
        public static Control _control;

        public void Load()
        {
            try
            {
                if (_assembly == null)
                {
                    _assembly = Assembly.Load(_dataAssembly);
                    _types = _assembly.GetTypes();
                }
           }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            _control = new Control();
            _control.SuspendLayout();
            LoadConfig();
            _control.ResumeLayout();
        }

        protected abstract void LoadConfig();
        protected IArea<T> DefineArea<T>(Action<T> a) 
            where T : new()
        {
            IArea<T> t = ((hasType<T>()) ? new ChelasUIArea<T>(a) : null);
            //T tmp = new T();
            //_control = tmp as Control;
            return t;
        }

        public Boolean hasType<T>()
        {
            Type tf = typeof(T);
            foreach (Type t in _types)
            {
                if( t.Name.Equals(tf.Name))
                        return true;
            }
            return false;
        }
   
    }

}