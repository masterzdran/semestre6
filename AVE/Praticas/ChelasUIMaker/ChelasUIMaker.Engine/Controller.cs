using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ChelasUIMaker.Engine
{
    public class Controller
    {
        private View view;
        public View View { get { return view; } set { view = value; } }
    }
}
