using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace MethodTestingAttributes
{
     [AttributeUsage(AttributeTargets.Method , AllowMultiple = false)]
    public class MethodTestAttribute:Attribute
    {
         string value;
         public MethodTestAttribute(string value)
        {
            this.value=value;
        }

         public override String ToString()
         {
             return String.Format(value);
         }
         public string Value
         {
             get { return value; }
             set { this.value = value; }
         }
    }
}
