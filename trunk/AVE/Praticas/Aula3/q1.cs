struct MyInt {public int x;}  
struct MyInt2 {public int x;} 

class Test{  
   static void m( ) { 
     MyInt v1; v1.x=1; 
     MyInt2 v2; v2.x=1; 
     v2=v1; 
 } 
} 
