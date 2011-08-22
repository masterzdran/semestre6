namespace ChelasUIMaker.Engine
{
    using System;

    public abstract class Config
    {
        public void Load()
        {
            

        }

        protected abstract void LoadConfig();


        protected IArea<T> DefineArea<T>(Action<T> a) 
            where T : new()
        {
            throw new NotImplementedException();
        }
    }
}