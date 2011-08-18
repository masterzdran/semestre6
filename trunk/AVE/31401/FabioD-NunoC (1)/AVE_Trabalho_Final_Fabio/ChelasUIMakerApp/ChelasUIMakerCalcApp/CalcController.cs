using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ChelasUIMaker.Engine;
using System.Windows.Forms;

namespace ChelasUIMakerCalcApp
{

    public class CalcController : Controller
    {
        enum State { Start, Digits, Oper, Error };
        State state = State.Start;

        long? number;
        Control _visor;
        int oper;


        private void error()
        {
            Visor.Text = "ERROR";
            number = null;
            oper = 0;
            state = State.Error;
        }

        private Control Visor
        {
            get
            {
                if (_visor == null) _visor = View["visor"];
                return _visor;
            }
        }
    }
}
      

