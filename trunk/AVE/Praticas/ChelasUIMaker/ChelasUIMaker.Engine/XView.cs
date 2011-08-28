
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
        private Form _formControl;
        public System.Windows.Forms.Form Control { get { return _formControl; } set { _formControl = value; } }

        public XView(Config config)
        {
            if (config == null) return;

            Control c = typeof(Config).GetField("_control").GetValue(config) as Control;
            if (c != null)
            {
                _formControl = new Form();
                processProperties(c);
            }

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
                fetchControlWithName(s, _formControl.Controls.Cast<Control>(), ref c);
                return c;
            }
            set
            {
                Control c = null;
                fetchControlWithName(s, _formControl.Controls.Cast<Control>(), ref c);
                if (c != null) c.Name = s;
            }
        }

        private void fetchControlWithName(string s, IEnumerable<Control> controls, ref Control c)
        {
            foreach (Control ctrl in controls)
            {
                if (ctrl.Name.Equals(s))
                {
                    c = ctrl;
                    return;
                }

                if (ctrl.Controls.Count > 0) fetchControlWithName(s, ctrl.Controls.Cast<Control>(), ref c);
            }
        }
        /*
        private void printAllCtrls(IEnumerable<Control> controls) //TODO debug
        {
            foreach (Control ctrl in controls)
            {
                Console.WriteLine("added control = " + ctrl + " :: with name = " + ctrl.Name);
                if (ctrl.Controls.Count > 0) printAllCtrls(ctrl.Controls.Cast<Control>());
            }
        }
        */
        /*TODO:*/
        private void processProperties(Control control)
        {
            _formControl.Controls.AddRange(control.Controls.Cast<Control>().ToArray());
            _formControl.Name = control.Name;
            _formControl.Text = control.Text;
            _formControl.Width = control.Width;
            _formControl.Height = control.Height;
        }

        private void processController(Object object_)
        {
            if (object_ == null) return;

            Type t = object_.GetType();

            var m = t.GetMethods(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.DeclaredOnly);

            foreach (var mi in m)
            {
                /*
                 * BNF Controller Handler
                 * <Handler Name> ::= [<context>'_'][<element>'_']<event>
                 * <Handler Name> ::= [Context][Element][Event]
                 * 
                 */

                String[] bnfHandler = mi.Name.Split('_');
                int size = bnfHandler.Length;
                String event_ = bnfHandler[bnfHandler.Length - 1]; 
                String element_ = (bnfHandler.Length < 3) ? null : bnfHandler[bnfHandler.Length - 2]; 
                //String context_ = (bnfHandler.Length >= 3) ? null : bnfHandler[bnfHandler.Length - 3]; 

                LinkedList<Control> control = new LinkedList<Control>();
                processControls(_formControl.Controls.Cast<Control>(), ref control, element_);
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
                    event_.AddEventHandler(c, Delegate.CreateDelegate(event_.EventHandlerType, object_, methodInfo, true));
            }
        }

        private void processControls(IEnumerable<Control> control, ref LinkedList<Control> list, String name)
        {
            if (control == null || list == null) return;

            foreach (Control c in control)
            {

                if (name == null || name.Trim().Equals("") || c.Name.Equals(name) || c.GetType().Name.Equals(name))
                {
                    list.AddFirst(c);
                    if (c.Controls.Count > 0) processControls(c.Controls.Cast<Control>(), ref list, name);
                }
            }
        }

    }
}