using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace ChelasUIMaker.Engine
{
    public class ViewEngine
    {
        public static XView LoadConfig(Config myConfig)
        {
            if (myConfig!=null)
            {
                myConfig.Load();
                return new MyView(myConfig).XView;
            }
            return null;
        }

        private class MyView : View
        {
            private readonly XView xview = new XView();

            public XView XView
            {
                get { return xview; }
            }

            public MyView(Config myConfig)
            {
                Control ctrl = typeof(Config).GetField("_graphics").GetValue(myConfig) as Control;

                if (ctrl != null)
                {
                    xview.Control = new Form();
                    MergeProperties(ctrl);
                }

                //get the controller 
                Type controllerType = typeof(Config).GetField("_controller").GetValue(myConfig) as Type;
                object concreteController = controllerType.GetConstructor(new Type[] { }).Invoke(null);

                //add controller to view
                AddControllerToView(concreteController);

                //set this view in the controler object
                if (controllerType != null) controllerType.GetProperty("View").SetValue(concreteController, this, null);
            }

            private void AddControllerToView(object obj) // melhorar pra adicionar os eventos de forma correcta ao Controllers correspondentes
            {
                Type o = obj.GetType();

                var p = o.GetMethods(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.DeclaredOnly);
                foreach (var methodInfo in p)
                {
                    var mtdName = methodInfo.Name;

                    var eventMtd = typeof(Control).GetEvent(mtdName);
                    if (eventMtd != null)
                    {
                        eventMtd.AddEventHandler(xview.Control, new EventHandler((sender, eventArgs) =>
                        {
                            methodInfo.Invoke(obj, new object[] { sender, eventArgs });
                        }));
                    }

                    RecursiveEventAdd(mtdName, xview.Control.Controls, methodInfo, obj);
                }
            }

            private void RecursiveEventAdd(string eventName, Control.ControlCollection controlCollection, MethodInfo methodInfo, object obj)
            {
                EventInfo evInfo;
                foreach (Control ctrl in controlCollection)
                {
                    evInfo = ctrl.GetType().GetEvent(eventName);
                    if (evInfo != null)
                    {
                        evInfo.AddEventHandler(ctrl, new EventHandler((sender, eventArgs) =>
                        {
                            methodInfo.Invoke(obj, new object[] { sender, eventArgs });
                        }));
                    }

                    if (ctrl.Controls.Count > 0)
                    {
                        RecursiveEventAdd(eventName, ctrl.Controls,methodInfo,obj);
                    }
                }
            }

            private void MergeProperties(Control ctrl)
            {
                // adiciono logo os controlos, pois ja sei que estes podem ser adicionados como array
                xview.Control.Controls.AddRange(ctrl.Controls.Cast<Control>().ToArray()); 

                xview.Control.Name = ctrl.Name;
                xview.Control.Text = ctrl.Text;
                xview.Control.Width = ctrl.Width;
                xview.Control.Height = ctrl.Height;


                // // dynamic add properties...
                //var controlProperties = typeof(Form).GetProperties(); // propriedades da classe de output (Form)
                //var inputProperties = typeof (Control).GetProperties(); // propriedades da classe de input (Control)


                //foreach (var controlProperty in controlProperties.Where((input) => !inputProperties.Contains(input)).OrderBy((input) => input.Name))
                //{
                //    if ( controlProperty.CanWrite && controlProperty.CanRead && !controlProperty.Name.Equals("Controls") ) // ja adicionei as propriedades dos controlos
                //    {
                //        Console.WriteLine("merging property = " + controlProperty.Name);

                //        controlProperty.SetValue(_control, controlProperty.GetValue(ctrl, null) , null);
                //    }
                //}
            }

            public override Control this[string s]
            {
                get 
                {   
                    Control c = null;
                    RecursiveSearchAndDeleteControl(s, ref c, xview.Control.Controls);
                    return c;
                }
                set
                {
                    Console.WriteLine("setting control = " + s + " :: to value = "+value);

                    Control c = null;
                    RecursiveSearchAndDeleteControl(s, ref c, xview.Control.Controls,true);
                    if(c!=null) 

                    xview.Control.Controls.Add(value);
                }
            }

            private void RecursiveSearchAndDeleteControl(string s, ref Control c, Control.ControlCollection controls, bool toDelete = false)
            {
                foreach (Control control in controls)
                {
                    if (control.Name.Equals(s))
                    {
                        c = control;
                        if (toDelete) controls.Remove(control);
                        break;
                    }
                    if (control.Controls.Count > 0) RecursiveSearchAndDeleteControl(s, ref c, control.Controls);
                }
            }
        }
    }
}
