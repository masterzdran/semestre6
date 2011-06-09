using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Alunos
{
    class Aluno
    {
        public int number;
        public String name;
        public Aluno() { name = "AVE"; }
        public Aluno(int nr, String name) { number = nr; this.name = name; }
        public String GetName() { return name; }
        public int GetNumber() { return number; }
    }
}
