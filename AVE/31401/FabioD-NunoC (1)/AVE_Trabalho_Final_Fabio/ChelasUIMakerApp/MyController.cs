using System;
using System.Windows.Forms;
using ChelasUIMaker.Engine;
namespace ChelasUIMakerApp
{
    public class MyController : Controller
    {

        protected void MouseEnter(object sender, EventArgs args)
        {
            Control c = (Control)sender;
            View["visor"].Text = sender.GetType().FullName + "(" + c.Name + ")";
        }

        protected void MouseLeave(object sender, EventArgs args)
        {
            
            Control c = (Control)sender;
            View["visor"].Text = "";
        }
    }
}

