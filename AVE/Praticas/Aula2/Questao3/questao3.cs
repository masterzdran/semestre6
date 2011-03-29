using System;
public struct A { public int x; }
//public struct C :A { public int y; }		//nao se pode derivar de tipos valores
public class B { public int w; }
public class D : B { public int z;}
public class Program{
	public static void Main(){
		A a = new A();
		Object o1 = a;		//boxing
		Object o2 = a;		//boxing
		B b= new D();		//conversao implicita
//		D d= new B();		//erro conversao - necessario conversao explicita
//		D d= (D) new B();	//erro em run-time!!
		D d= (D) new D();
//		o1.x = 2;			//necessario cast para fazer unboxing
		A aux1= ((A) o1);
		aux1.x=2;
//		( (A) o2 ). x = 4;	//nao se pode fazer unboxing de um tipo valor
		A aux2= ( (A) o2 );
		aux2.x = 4;
//		A k = o2;			//necessario cast para unboxing
		A k = (A) o2;						
		((D) b).z=3;
		Console.WriteLine(a);
		Console.WriteLine(k);
		Console.WriteLine(o1);
		Console.WriteLine(o2);
		Console.WriteLine(b);
		Console.WriteLine(d);
	}
}
