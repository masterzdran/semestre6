using System; 
 
class B1{ 
  public override bool Equals(object o){ 
        B1 b1 = o as B1; 
        if(b1==null) return false; 
        return true; 
  }
  public override int GetHashCode(){
	return 1;  
  }
} 
class B2{ 
  public override bool Equals(object o){ 
    if(o ==null || o.GetType() != typeof(B2) ) return false; 
        return true; 
  }
  public override int GetHashCode(){
	return 2;  
  }  
}        
class B3 { 
  public override bool Equals(object o){ 
    if(o ==null || o.GetType() != GetType() ) return false; 
        return true; 
        }
  public override int GetHashCode(){
	return 3;  
  }
} 
class B11 : B1{   } 
class B22 : B2{   } 
class B33 : B3{   }   
  
class Program{ 
  public static void Main(){ 
   B11 a =new B11(); 
   B1 b = new B1(); 
   B22 c = new B22(); 
   B2 d = new B2(); 
   B3 e = new B3(); 
   B33 f = new B33(); 
   Console.WriteLine(a.Equals(b)); 
   Console.WriteLine(c.Equals(d)); 
   Console.WriteLine(e.Equals(f)); 
  } 
} 
