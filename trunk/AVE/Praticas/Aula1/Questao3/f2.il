
//  Microsoft (R) .NET Framework IL Disassembler.  Version 4.0.30319.1
//  Copyright (c) Microsoft Corporation.  All rights reserved.



// Metadata version: v2.0.50727
.module extern f1new.dll
.module extern f3new.dll
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 2:0:0:0
}
.assembly f2
{
  .custom instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
                                                                                                             63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )       // ceptionThrows.
  .custom instance void [mscorlib]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::.ctor(int32) = ( 01 00 08 00 00 00 00 00 ) 
  .hash algorithm 0x00008004
  .ver 0:0:0:0
}
.file f1new.dll
    .hash = (12 4C 97 1C 12 58 FD A3 DA 20 D7 07 FC 0E 99 5C   // .L...X... .....\
             B0 34 A0 92 )                                     // .4..
.file f3new.dll
    .hash = (2A 6A D5 3F CC A6 D4 93 A2 C7 87 8F 07 01 6E 31   // *j.?..........n1
             94 DA 26 9C )                                     // ..&.
.class extern public C1
{
  .file f1new.dll
  .class 0x02000002
}
.class extern public C3
{
  .file f3new.dll
  .class 0x02000002
}
.module f2.dll
// MVID: {E50B21D5-6CF9-4A29-807D-C7E7A0120137}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003       // WINDOWS_CUI
.corflags 0x00000001    //  ILONLY
// Image base: 0x003D0000


// =============== CLASS MEMBERS DECLARATION ===================

.class public auto ansi beforefieldinit C2
       extends [mscorlib]System.Object
{
  .method private hidebysig static void  Main() cil managed
  {
    .entrypoint
    // Code size       68 (0x44)
    .maxstack  2
    .locals init (class [.module f1new.dll]C1 V_0,
             class [.module f3new.dll]C3 V_1)
    IL_0000:  newobj     instance void [.module f1new.dll]C1::.ctor()
    IL_0005:  stloc.0
    IL_0006:  newobj     instance void [.module f3new.dll]C3::.ctor()
    IL_000b:  stloc.1
    IL_000c:  ldloc.0
    IL_000d:  ldc.r8     20.5
    IL_0016:  callvirt   instance void [.module f1new.dll]C1::saveFloat(float64)
    IL_001b:  ldloc.1
    IL_001c:  ldc.i4.3
    IL_001d:  callvirt   instance void [.module f3new.dll]C3::saveInt(int32)
    IL_0022:  ldloc.0
    IL_0023:  callvirt   instance float64 [.module f1new.dll]C1::getFloat()
    IL_0028:  ldloc.1
    IL_0029:  callvirt   instance int32 [.module f3new.dll]C3::getInt()
    IL_002e:  conv.r8
    IL_002f:  add
    IL_0030:  call       void [mscorlib]System.Console::WriteLine(float64)
    IL_0035:  ldc.i4.s   10
    IL_0037:  ldloc.1
    IL_0038:  callvirt   instance int32 [.module f3new.dll]C3::getInt()
    IL_003d:  add
    IL_003e:  call       void [mscorlib]System.Console::WriteLine(int32)
    IL_0043:  ret
  } // end of method C2::Main

  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    // Code size       7 (0x7)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [mscorlib]System.Object::.ctor()
    IL_0006:  ret
  } // end of method C2::.ctor

} // end of class C2


// =============================================================

// *********** DISASSEMBLY COMPLETE ***********************
// WARNING: Created Win32 resource file f2.res
