namespace ChelasUIMaker.Extensions
{
    using System;
    using System.Collections.Generic;
    using System.Drawing;
    using System.Linq;
    using System.Text;
    using System.Windows.Forms;

    public static class ControlExtensions
    {
        public static Control SetFont(this Control ctrl, string font)
        {
            var x = font.Split(',');
            
            ctrl.Font = new Font(x[0],Int16.Parse(x[1]));
            return ctrl;
        }

        public static Control SetBackColor(this Control ctrl, int colorArgb)
        {
            ctrl.BackColor = Color.FromArgb(colorArgb);
            return ctrl;
        }

    }
}
