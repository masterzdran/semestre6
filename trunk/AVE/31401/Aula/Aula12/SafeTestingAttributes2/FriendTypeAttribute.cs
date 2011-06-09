using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SafeTestingAttributes2
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple=true)]
    class FriendType2Attribute:Attribute
    {
         Type value;
         public FriendType2Attribute(Type value)
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

