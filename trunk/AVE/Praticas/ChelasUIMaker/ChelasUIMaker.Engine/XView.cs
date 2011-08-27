
namespace ChelasUIMaker.Engine
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Windows.Forms;
    using System.Reflection;
    public class XView : View
    {
        private Form _control ;
        public System.Windows.Forms.Form Control { get { return _control; } set { _control = value; } }

        public XView(Config config)
        {
            if (config == null) return;

            //Control c = config.Area.GetType().GetField("_Control").GetValue(config) as Control;
            Control c = typeof(Config).GetField("_control").GetValue(config) as Control;
            if (c == null) return;

            _control = new Form();
            processProperties(c);

            //Type t = config.Area.GetType().GetField("_controller").GetValue(config) as Type;
            Type t = typeof(Config).GetField("_controller").GetValue(config) as Type;
            
            object o = t.GetConstructor(new Type[] { }).Invoke(null);
 
            //add controller to view
            processController(o);

            //set view in the controller
            if (t != null) t.GetProperty("View").SetValue(o, this, null);
 
        }

        public override System.Windows.Forms.Control this[string s]
        {
            get
            {
                Control c = null;
                processControl(s, ref c, _control.Controls);
                return c;
            }
            set
            {
                Control c = null;
                processControl(s, ref c, _control.Controls, true);
                if (c != null)
                    _control.Controls.Add(value);
            }
        }
        /*TODO:*/
        private void processProperties(Control control)
        {
            _control.Controls.AddRange(control.Controls.Cast<Control>().ToArray());
            _control.Name = control.Name;
            _control.Text = control.Text;
            _control.Width = control.Width;
            _control.Height = control.Height;
        }

        private void processController(Object object_)
        {
            if (object_ == null) return;

            Type t = object_.GetType();

            var m = t.GetMethods(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.DeclaredOnly);

            foreach (var mi in m)
            {
                String[] bnfHandler = mi.Name.Split('_');
                String event_ = bnfHandler[bnfHandler.Length - 1];
                String element_ = (bnfHandler.Length < 2) ? null : bnfHandler[bnfHandler.Length - 2];
                String context_ = (bnfHandler.Length < 3) ? null : bnfHandler[bnfHandler.Length - 3];

                LinkedList<Control> control = new LinkedList<Control>();
                processControls(_control.Controls.Cast<Control>(), ref control, element_);
                AddHandler(control, object_, event_, mi);
            }
            

        }

        private void AddHandler(IEnumerable<Control> control, Object object_, String name, MethodInfo methodInfo)
        {
            EventInfo event_;
            foreach (Control c in control)
            {
                event_ = typeof(Control).GetEvent(name);
                if (event_ != null)
                    event_.AddEventHandler(control,Delegate.CreateDelegate(event_.EventHandlerType, object_, methodInfo, true));
            }
        }

        private void processControls(IEnumerable<Control> control, ref LinkedList<Control> list, String name)
        {
            if (control == null || list == null) return;

            foreach (Control c in control){

                if (name == null || name.Trim().Equals("") || c.Name.Equals(name) || c.GetType().Name.Equals(name)){
                    list.AddFirst(c);
                    if (c.Controls.Count > 0) processControls(c.Controls.Cast<Control>(), ref list, name);
                }                
            }
        }

        private void processControl(String name, ref Control control_, Control.ControlCollection list, Boolean b=false)
        {
            if (name == null || control_ == null || list == null) return;
            foreach (Control c in list)
            {
                if (c.Name.Equals(name))
                {
                    control_ = c;
                    if (b) list.Remove(c);
                    break;
                }
                if (c.Controls.Count > 0) processControl(name, ref control_, c.Controls);
            }
        }
    }
}