using System; 
struct S{ 
        public int x; 
}

class Program{ 
  public static void Main(){ 
     S a=new S(); 
     a.x=1; 
     S b=new S(); 
     b.x=1; 
     //Console.WriteLine(a==b); //não se pode utilizar o comparador == para comparar structs
     Console.WriteLine(a.Equals(b)); 
     Console.WriteLine(ReferenceEquals(a,b)); 
  } 
}   
