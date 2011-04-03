using System; 
class A{ 
  public  void  F(){ Console.WriteLine("A.F"); } 
  public virtual void G(){ Console.WriteLine( " A.G");}  
} 
class B: A{ 
  public void F(){ Console.WriteLine("B.F");} 
  public override void G() { Console.WriteLine("B.G");} 
}  

class Test{ 
	static void Main(){ 
	  B b = new B(); 
	  A a = new B(); 
	  a.F(); 
	  b.F(); 
	  a.G(); 
		b.G(); 
	  } 
} 
