using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ChelasUIMaker.Engine
{
    public class ViewEngine
    {
        public static XView LoadConfig(Config myConfig)
        {
            if (myConfig == null)
                throw new InvalidOperationException();

            myConfig.Load();
            return new XView(myConfig);
        }
    }
}
