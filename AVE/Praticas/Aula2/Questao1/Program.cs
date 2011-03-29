using System;

class SomeClassInCSharp : SomeClassInVB
{
	public override void M1()
	{
		Console.WriteLine("M1 from CSharp");
		base.M1();
	}
}

class Program
{
	static void Main(string[] args)
	{
		SomeClassInCSharp t = new SomeClassInCSharp();
		t.M1();
	}
}
