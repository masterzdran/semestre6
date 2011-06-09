using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MethodTestingAttributes
{
    class TestClass
    {
        [MethodTest("False")]
        public static bool xpto1()
        {
            return true;
        }

        [MethodTest("False")]
        public static bool xpto2()
        {
            return false;
        }
    }
}
