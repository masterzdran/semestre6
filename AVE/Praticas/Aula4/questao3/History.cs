using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace CollectionClasses1
{
    class History<E> : IEnumerable<E>
    {
        private E[] elements;

        public History(Int32 size) 
        {
            //Inicializa o array de elementos com o tamanho passado
            elements = new E[size];
        }

        //Implementação da interface IEnumerable
        public IEnumerator GetEnumerator()
        {
            return new HistoryEnumerator(this);
        }


        private class HistoryEnumerator : IEnumerator
        {
            //indice de Head (1º da lista)
            private Int32 get;
            //indice do último da lista
            private Int32 put;
            //indice do elemento que o enumerador está a consultar
            private Int32 index;
            private History<E> h;

            public HistoryEnumerator(History<E> h)
            {
                this.h = h;
                get = put = index = 0;
            }

            //devolve o objecto no indice index
            public object Current
            {
                get 
                { 
                    return h.elements[index]; 
                }
            }

            //move o indice index para o próximo elemento se houver
            //se index for igual a put já está no ultimo elemento
            public bool MoveNext()
            {
                if (index != put)
                {
                    index = (++index % h.elements.Length);
                    return true;
                }
                else 
                {
                    return false;
                }

            }

            //coloca o indice no primeiro elemento (get) da lista
            public void Reset()
            {
                index = get;
            }
            
            //adiciona um elemento na lista. Se lista estiver cheia (indice do ultimo elemento - put -
            //for igual ao primeiro - get - avança para o "próximo" primeiro elemento
            //se index estiver colocado no primeiro elemento faz "reset"
            public void Add(E element)
            {
                put = (++put % h.elements.Length);
                h.elements[put] = element;
                if (get == put)
                {
                    get = (++get% h.elements.Length);
                }
                if (index == put) 
                {
                    index = get;
                }

            }

            public E Head()
            {
                return h.elements[get];
            }

        }
    }
}
