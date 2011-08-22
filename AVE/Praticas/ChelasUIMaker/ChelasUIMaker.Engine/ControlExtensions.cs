// -----------------------------------------------------------------------
// <copyright file="ControlExtensions.cs" company="Microsoft">
// TODO: Update copyright text.
// </copyright>
// -----------------------------------------------------------------------

namespace ChelasUIMaker.Engine
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
            //ctrl.Font = new Font(font);
            return ctrl;
        }

        public static Control SetBackColor(this Control ctrl, int colorArgb)
        {
            ctrl.BackColor = Color.FromArgb(colorArgb);
            return ctrl;
        }

    }
}

