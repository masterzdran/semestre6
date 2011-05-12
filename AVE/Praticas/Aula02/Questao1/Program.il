
//  Microsoft (R) .NET Framework IL Disassembler.  Version 4.0.30319.1
//  Copyright (c) Microsoft Corporation.  All rights reserved.


// Classes defined in this module:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Class SomeClassInCSharp              (auto) (ansi) 
// Class Program                        (auto) (ansi) 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// Metadata version: v4.0.30319
.module extern SomeClassInVB.netmodule
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 4:0:0:0
}
.assembly extern Microsoft.VisualBasic
{
  .publickeytoken = (B0 3F 5F 7F 11 D5 0A 3A )                         // .?_....:
  .ver 10:0:0:0
}
.assembly Program
{
  .custom instance void [mscorlib]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::.ctor(int32) = ( 01 00 08 00 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
                                                                                                             63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )       // ceptionThrows.
  .hash algorithm 0x00008004
  .ver 0:0:0:0
}
.file SomeClassInVB.netmodule
    .hash = (4D 0C 35 D4 18 D6 3D 5E B2 B4 E6 F8 49 60 82 3D   // M.5...=^....I`.=
             E0 60 53 D0 )                                     // .`S.
.class extern public SomeClassInVB
{
  .file SomeClassInVB.netmodule
  .class 0x02000002
}
.module Program.exe
// MVID: {0B2DB912-A8AF-4F4A-BA9E-1FB3777E9AB1}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003       // WINDOWS_CUI
.corflags 0x00000001    //  ILONLY
// Image base: 0x005A0000


// =============== CLASS MEMBERS DECLARATION ===================

.class private auto ansi beforefieldinit SomeClassInCSharp
       extends [.module SomeClassInVB.netmodule]SomeClassInVB
{
  .method public hidebysig virtual instance void 
          M1() cil managed
  {
    // Code size       20 (0x14)
    .maxstack  8
    IL_0000:  nop
    IL_0001:  ldstr      "M1 from CSharp"
    IL_0006:  call       void [mscorlib]System.Console::WriteLine(string)
    IL_000b:  nop
    IL_000c:  ldarg.0
    IL_000d:  call       instance void [.module SomeClassInVB.netmodule]SomeClassInVB::M1()
    IL_0012:  nop
    IL_0013:  ret
  } // end of method SomeClassInCSharp::M1

  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    // Code size       7 (0x7)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [.module SomeClassInVB.netmodule]SomeClassInVB::.ctor()
    IL_0006:  ret
  } // end of method SomeClassInCSharp::.ctor

} // end of class SomeClassInCSharp

.class private auto ansi beforefieldinit Program
       extends [mscorlib]System.Object
{
  .method private hidebysig static void  Main(string[] args) cil managed
  {
    .entrypoint
    // Code size       15 (0xf)
    .maxstack  1
    .locals init (class SomeClassInCSharp V_0)
    IL_0000:  nop
    IL_0001:  newobj     instance void SomeClassInCSharp::.ctor()
    IL_0006:  stloc.0
    IL_0007:  ldloc.0
    IL_0008:  callvirt   instance void [.module SomeClassInVB.netmodule]SomeClassInVB::M1()
    IL_000d:  nop
    IL_000e:  ret
  } // end of method Program::Main

  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    // Code size       7 (0x7)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [mscorlib]System.Object::.ctor()
    IL_0006:  ret
  } // end of method Program::.ctor

} // end of class Program


// =============================================================

// *********** DISASSEMBLY COMPLETE ***********************
// WARNING: Created Win32 resource file D:\ISEL\Semestre6\AVE\Praticas\Aula2\Questao1\Program.res
