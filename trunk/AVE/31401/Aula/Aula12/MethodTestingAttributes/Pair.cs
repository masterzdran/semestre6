using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MethodTestingAttributes
{
    public class Pair<T, W>
    {
        public T t;
        public W w;

        public T MyT
        {
            get { return t; }
            set
            {
                t = value;
            }
        }

        public W MyW
        {
            get { return w; }
            set
            {
                w = value;
            }
        }



    }
}
