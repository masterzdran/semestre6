using System;
using System.Collections;

public class Tokens : IEnumerable
{
   private string[] elements;

   public Tokens(string source, char[] delimiters)
   {
      // Parsing de uma String em tokens:
      elements = source.Split(delimiters);
   }

   // Implementação da interfaxe IEnumerable
   public IEnumerator GetEnumerator()
   {
      return new TokenEnumerator(this);
   }

   /**
    *  Inicialmente, o enumerador está posicionado antes do primeiro elemento na colecção.
    *  O método Reset faz com que o enumerador retorne à sua posição.
    *  Nesta posição, a invocação da propriedade Current faz com que seja lançada uma excepção. 
    *  Deste modo, tem que se invocar de avanço o método MoveNext para avançar o enumerador para o primeiro elemento, 
    *  antes da leitura do valor actual.
    */
   private class TokenEnumerator : IEnumerator
   {
      private int position = -1;
      private Tokens t;

      public TokenEnumerator(Tokens t)
      {
         this.t = t;
      }

      public bool MoveNext()
      {
         if (position < t.elements.Length - 1)
         {
            position++;
            return true;
         }
         else
         {
            return false;
         }
      }

      public void Reset()
      {
         position = -1;
      }

      public object Current
      {
         get
         {
            return t.elements[position];
         }
      }
   }

}

