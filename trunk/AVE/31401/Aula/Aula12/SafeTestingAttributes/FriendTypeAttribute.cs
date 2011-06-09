using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SafeTestingAttributes
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple=true)]
    class FriendTypeAttribute:Attribute
    {
         Type value;
         public FriendTypeAttribute(Type value)
        {
            
            this.value=value;
        }

         public override String ToString()
         {
             return String.Format(value.ToString());
         }
         public Type Value
         {
             get { return value; }
             set { this.value = value; }
         }
    }
    }

