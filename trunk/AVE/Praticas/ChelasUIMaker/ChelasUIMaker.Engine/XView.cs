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

        Config _config;
        
        public XView(Config config)
        {
            if (config == null) return;

            _config = config;
            Type x = config.IArea.GetType();
            Control c = new Control();
            
            if (c != null)
            {
                _formControl = new Form();
                processProperties(c);
            }
            Type t = config.GetType();
            
            //object o = t.GetConstructor(new Type[] { }).Invoke(null);

            processController(t);

            //set view in the controller
            if (t != null) t.GetProperty("View").SetValue(t, this, null);
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

        private void processProperties(Control control)
        {
            _formControl.Controls.AddRange(control.Controls.Cast<Control>().ToArray());
            _formControl.Name = control.Name;
            _formControl.Text = control.Text;
            _formControl.Width = control.Width;
            _formControl.Height = control.Height;
        }

        private void processController(Type t)
        {
            if (t == null) return;

            //Type t = object_;

            MessageBox.Show(t.BaseType.Name);

            MethodInfo[] m = t.GetMethods(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.DeclaredOnly);
            String[] bnfHandler;
            int size;
            String event_, element_, context_;
            
            foreach (MethodInfo mi in m)
            {
                /*
                 * BNF Controller Handler
                 * <Handler Name> ::= [<context>'_'][<element>'_']<event>
                 * <Handler Name> ::= [Context][Element][Event]
                 * 
                 */

                bnfHandler = mi.Name.Split('_');
                size = bnfHandler.Length;
                event_ = bnfHandler[bnfHandler.Length - 1]; 
                element_ = (bnfHandler.Length < 2) ? null : bnfHandler[bnfHandler.Length - 2]; 
                context_ = (bnfHandler.Length < 3) ?  null : bnfHandler[bnfHandler.Length - 3]; 

                LinkedList<Control> control = new LinkedList<Control>();

                processControls(_formControl.Controls.Cast<Control>(), ref control, element_);
                AddHandler(control, t, event_, mi);
            }
        }

        private void AddHandler(IEnumerable<Control> control, Type object_, String name, MethodInfo methodInfo)
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