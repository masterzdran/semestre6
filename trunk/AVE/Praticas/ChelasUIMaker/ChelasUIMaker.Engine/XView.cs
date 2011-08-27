
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
        private Form _formControl ;
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
                processControl(s, ref c, this._formControl.Controls);
                return c;
            }
            set
            {
                Control c = null;
                processControl(s, ref c, this._formControl.Controls, true);
                if (c != null)
                    this._formControl.Controls.Add(value);
            }
        }
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
                String[] bnfHandler = mi.Name.Split('_');
                String event_ = bnfHandler[bnfHandler.Length - 1];
                String element_ = (bnfHandler.Length < 2) ? null : bnfHandler[bnfHandler.Length - 2];
                String context_ = (bnfHandler.Length < 3) ? null : bnfHandler[bnfHandler.Length - 3];

                LinkedList<Control> control = new LinkedList<Control>();
                processControls(_formControl.Controls.Cast<Control>(), ref control, element_);
                AddHandler(control, object_, event_, mi);
            }
            

        }

        private void FetchAllControls(IEnumerable<Control> iEnumerable, ref LinkedList<Control> ctrls, string typeNameOrControlName = "")
        {
            foreach (Control control in iEnumerable)
            {
                if (typeNameOrControlName.Equals("")) ctrls.AddFirst(control);
                if (!typeNameOrControlName.Equals("") && (control.Name.Equals(typeNameOrControlName) || control.GetType().Name.Equals(typeNameOrControlName))) ctrls.AddFirst(control);
                if (control.Controls.Count > 0) FetchAllControls(control.Controls.Cast<Control>(), ref ctrls, typeNameOrControlName);
            }
        }
        private void AddControllerToView(object obj) // melhorar pra adicionar os eventos de forma correcta ao Controllers correspondentes
        {
            Type o = obj.GetType();

            var p = o.GetMethods(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.DeclaredOnly);


            foreach (var methodInfo in p)
            {
                string[] BNF = methodInfo.Name.Split('_');

                if (BNF.Length == 1) // caso em que é adicionado a todos os controlos
                {
                    LinkedList<Control> allCtrls = new LinkedList<Control>();
                    FetchAllControls(_formControl.Controls.Cast<Control>(), ref allCtrls);

                    AddEventHandler(BNF[0], obj, methodInfo, allCtrls);
                }

                // ir buscar todos os controlos do tipo BNF[0]...
                LinkedList<Control> ctrls = new LinkedList<Control>();
                FetchAllControls(_formControl.Controls.Cast<Control>(), ref ctrls, BNF[0]);

                if (BNF.Length == 2) // caso em que é adicionado a todos os controlos do tipo BNF[0] e nome do evento BNF[1]
                {
                    // ...a todos estes, adicionar o eventhandler de nome BNF[1]
                    AddEventHandler(BNF[1], obj, methodInfo, ctrls);
                }

                if (BNF.Length == 3) // caso em que é adicionado a todos os controlos do tipo BNF[1] dentro dos controlos BNF[0] e nome do evento BNF[1]
                {
                    // ...ir buscar todos os controlos do tipo ou nome BNF[1] dentro dos anteriores...
                    LinkedList<Control> ctrls2 = new LinkedList<Control>();
                    FetchAllControls(ctrls, ref ctrls2, BNF[1]);

                    // ...a todos estes, adicionar o eventhandler de nome BNF[2]
                    AddEventHandler(BNF[2], obj, methodInfo, ctrls2);
                }
            }
        }

        private void AddEventHandler(string eventName, object obj, MethodInfo methodInfo, IEnumerable<Control> ctrls)
        {
            EventInfo eventMtd;
            foreach (Control control in ctrls)
            {
                eventMtd = typeof(Control).GetEvent(eventName);
                if (eventMtd != null)
                {
                    eventMtd.AddEventHandler(
                        control,
                        Delegate.CreateDelegate(eventMtd.EventHandlerType, obj, methodInfo, true)
                    );
                }
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