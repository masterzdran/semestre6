using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ChelasUIMaker.Engine
{
    class ChelasUIView : View , XView
    {

        public ChelasUIView(Config config)
        {

        }

        
        public override System.Windows.Forms.Control this[string s]
        {
            get
            {
                throw new NotImplementedException();
            }
            set
            {
                throw new NotImplementedException();
            }
        }
    }
}
