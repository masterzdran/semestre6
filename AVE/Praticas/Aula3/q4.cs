using System;

struct Point {  
	int x, y;  
	public Point(int x, int y) {  
		this.x=x; this.y=y;  
	}  
	public void add( Point p, ref Point res) {  
		res = this;  
		res.x += p.x;  
		res.y += p.y;  
	}  
	public override String ToString() {  
		return String.Format("({0},{1})", x, y);  
	}  
}  

class Program {  
static void Main(string[] args){  
  Point p1 = new Point(1, 2),  
  p2 = new Point(3, 4);  
  p1.add(p2, ref p2);  
  Console.WriteLine("p1={0}, p2={1}", p1,p2);  
}  
}  
