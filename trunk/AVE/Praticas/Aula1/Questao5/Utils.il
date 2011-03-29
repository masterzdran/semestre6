.assembly extern mscorlib {
	.publickeytoken = (B7 7A 5C 56 19 34 E0 89 )
	.ver 2:0:0:0
}
.assembly what {
	.ver 1:0:0:0
}
.namespace Utils {
	.class public auto Globals 	{
	
		.method public static void recursiveOperation(int32 n) cil managed {
			.maxstack 2
			ldarg.0
			ldc.i4.s 10
			bge.s label1
			ldarg.0
			call void [mscorlib]System.Console::Write(int32)
			br.s label2
			label1:
			ldarg.0
			ldc.i4.s 10
			div
			call void Utils.Globals::recursiveOperation (int32)
			ldarg.0
			ldc.i4.s 10
			rem
			ldc.i4.s 10
			call void [mscorlib]System.Console::Write(char)
			call void [mscorlib]System.Console::Write(int32)
			label2:
			ret
		} // end of method
	}
}
