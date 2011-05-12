using System;

struct Counter{ 
  int value; 
  public override string ToString() { 
    return value.ToString(); 
  } 
  public void Increment() { value++;  } 
} 

class Program  { 
   static void Main() { 
      Counter x = new Counter(); 
      object o = x; 
      x.Increment(); Console.WriteLine(x.ToString()); 
      Console.WriteLine(o);                                           
      ((Counter)o).Increment(); Console.WriteLine(o);       
      Counter c = (Counter)x; 
      c.Increment(); Console.WriteLine(c);     
      Console.WriteLine(x);        
   } 
} 
