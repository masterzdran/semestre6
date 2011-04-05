using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CollectionClasses1
{
    class Token1
    {
        private string[] elements;

       public Token1(string source, char[] delimiters)
        {
            // Parsing de uma String em tokens:
            elements = source.Split(delimiters);
        }

        // Implementação da interface IEnumerable
        public IEnumerator GetEnumerator()
        {
           
            //yield return (para retornar o próximo item) 
            int currentposition = -1;

            while (currentposition != elements.Length-1)
            {
                yield return elements[++currentposition];
             
            }
        }

       
    }
}


