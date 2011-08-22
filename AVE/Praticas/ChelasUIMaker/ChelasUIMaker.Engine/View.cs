using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ChelasUIMaker.Engine
{

    public abstract class View
    {
        public abstract Control this[String s] { get; set; }
    }
}
