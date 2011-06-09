
//  Microsoft (R) .NET Framework IL Disassembler.  Version 4.0.30319.1
//  Copyright (c) Microsoft Corporation.  All rights reserved.



// Metadata version: v4.0.30319
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 4:0:0:0
}
.assembly Reflection
{
  .custom instance void [mscorlib]System.Runtime.Versioning.TargetFrameworkAttribute::.ctor(string) = ( 01 00 29 2E 4E 45 54 46 72 61 6D 65 77 6F 72 6B   // ..).NETFramework
                                                                                                        2C 56 65 72 73 69 6F 6E 3D 76 34 2E 30 2C 50 72   // ,Version=v4.0,Pr
                                                                                                        6F 66 69 6C 65 3D 43 6C 69 65 6E 74 01 00 54 0E   // ofile=Client..T.
                                                                                                        14 46 72 61 6D 65 77 6F 72 6B 44 69 73 70 6C 61   // .FrameworkDispla
                                                                                                        79 4E 61 6D 65 1F 2E 4E 45 54 20 46 72 61 6D 65   // yName..NET Frame
                                                                                                        77 6F 72 6B 20 34 20 43 6C 69 65 6E 74 20 50 72   // work 4 Client Pr
                                                                                                        6F 66 69 6C 65 )                                  // ofile
  .custom instance void [mscorlib]System.Reflection.AssemblyTitleAttribute::.ctor(string) = ( 01 00 0A 52 65 66 6C 65 63 74 69 6F 6E 00 00 )    // ...Reflection..
  .custom instance void [mscorlib]System.Reflection.AssemblyDescriptionAttribute::.ctor(string) = ( 01 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Reflection.AssemblyConfigurationAttribute::.ctor(string) = ( 01 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Reflection.AssemblyCompanyAttribute::.ctor(string) = ( 01 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Reflection.AssemblyProductAttribute::.ctor(string) = ( 01 00 0A 52 65 66 6C 65 63 74 69 6F 6E 00 00 )    // ...Reflection..
  .custom instance void [mscorlib]System.Reflection.AssemblyCopyrightAttribute::.ctor(string) = ( 01 00 12 43 6F 70 79 72 69 67 68 74 20 C2 A9 20   // ...Copyright .. 
                                                                                                  20 32 30 31 31 00 00 )                            //  2011..
  .custom instance void [mscorlib]System.Reflection.AssemblyTrademarkAttribute::.ctor(string) = ( 01 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Runtime.InteropServices.ComVisibleAttribute::.ctor(bool) = ( 01 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Runtime.InteropServices.GuidAttribute::.ctor(string) = ( 01 00 24 65 32 33 63 33 62 66 64 2D 62 34 66 30   // ..$e23c3bfd-b4f0
                                                                                                  2D 34 31 39 34 2D 39 66 30 33 2D 32 33 65 33 39   // -4194-9f03-23e39
                                                                                                  37 63 37 32 38 62 39 00 00 )                      // 7c728b9..
  .custom instance void [mscorlib]System.Reflection.AssemblyFileVersionAttribute::.ctor(string) = ( 01 00 07 31 2E 30 2E 30 2E 30 00 00 )             // ...1.0.0.0..

  // --- The following custom attribute is added automatically, do not uncomment -------
  //  .custom instance void [mscorlib]System.Diagnostics.DebuggableAttribute::.ctor(valuetype [mscorlib]System.Diagnostics.DebuggableAttribute/DebuggingModes) = ( 01 00 07 01 00 00 00 00 ) 

  .custom instance void [mscorlib]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::.ctor(int32) = ( 01 00 08 00 00 00 00 00 ) 
  .custom instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
                                                                                                             63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )       // ceptionThrows.
  .hash algorithm 0x00008004
  .ver 1:0:0:0
}
.module Reflection.exe
// MVID: {860D970B-9C31-4EBF-9809-B28E4C705690}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003       // WINDOWS_CUI
.corflags 0x00000003    //  ILONLY 32BITREQUIRED
// Image base: 0x01480000


// =============== CLASS MEMBERS DECLARATION ===================

.class private auto ansi beforefieldinit Alunos.Program
       extends [mscorlib]System.Object
{
  .method private hidebysig static void  Main(string[] args) cil managed
  {
    .entrypoint
    // Code size       158 (0x9e)
    .maxstack  4
    .locals init ([0] class [mscorlib]System.Type myTypeObj,
             [1] object a2,
             [2] class [mscorlib]System.Type t,
             [3] class [mscorlib]System.Reflection.MethodInfo m,
             [4] string s,
             [5] object a3,
             [6] string ss,
             [7] class [mscorlib]System.Exception e,
             [8] object[] CS$0$0000)
    IL_0000:  nop
    IL_0001:  nop
    IL_0002:  ldstr      "Alunos.Aluno"
    IL_0007:  call       class [mscorlib]System.Type [mscorlib]System.Type::GetType(string)
    IL_000c:  stloc.0
    IL_000d:  ldloc.0
    IL_000e:  call       object [mscorlib]System.Activator::CreateInstance(class [mscorlib]System.Type)
    IL_0013:  stloc.1
    IL_0014:  ldloc.1
    IL_0015:  callvirt   instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
    IL_001a:  stloc.2
    IL_001b:  ldloc.2
    IL_001c:  ldstr      "GetName"
    IL_0021:  callvirt   instance class [mscorlib]System.Reflection.MethodInfo [mscorlib]System.Type::GetMethod(string)
    IL_0026:  stloc.3
    IL_0027:  ldloc.3
    IL_0028:  ldloc.1
    IL_0029:  ldnull
    IL_002a:  callvirt   instance object [mscorlib]System.Reflection.MethodBase::Invoke(object,
                                                                                        object[])
    IL_002f:  castclass  [mscorlib]System.String
    IL_0034:  stloc.s    s
    IL_0036:  ldloc.s    s
    IL_0038:  call       void [mscorlib]System.Console::WriteLine(string)
    IL_003d:  nop
    IL_003e:  ldloc.0
    IL_003f:  ldc.i4.2
    IL_0040:  newarr     [mscorlib]System.Object
    IL_0045:  stloc.s    CS$0$0000
    IL_0047:  ldloc.s    CS$0$0000
    IL_0049:  ldc.i4.0
    IL_004a:  ldc.i4.3
    IL_004b:  box        [mscorlib]System.Int32
    IL_0050:  stelem.ref
    IL_0051:  ldloc.s    CS$0$0000
    IL_0053:  ldc.i4.1
    IL_0054:  ldstr      "Alice"
    IL_0059:  stelem.ref
    IL_005a:  ldloc.s    CS$0$0000
    IL_005c:  call       object [mscorlib]System.Activator::CreateInstance(class [mscorlib]System.Type,
                                                                           object[])
    IL_0061:  stloc.s    a3
    IL_0063:  ldloc.s    a3
    IL_0065:  callvirt   instance class [mscorlib]System.Type [mscorlib]System.Object::GetType()
    IL_006a:  ldstr      "GetName"
    IL_006f:  callvirt   instance class [mscorlib]System.Reflection.MethodInfo [mscorlib]System.Type::GetMethod(string)
    IL_0074:  ldloc.s    a3
    IL_0076:  ldnull
    IL_0077:  callvirt   instance object [mscorlib]System.Reflection.MethodBase::Invoke(object,
                                                                                        object[])
    IL_007c:  castclass  [mscorlib]System.String
    IL_0081:  stloc.s    ss
    IL_0083:  ldloc.s    ss
    IL_0085:  call       void [mscorlib]System.Console::WriteLine(string)
    IL_008a:  nop
    IL_008b:  nop
    IL_008c:  leave.s    IL_009c

    IL_008e:  stloc.s    e
    IL_0090:  nop
    IL_0091:  ldloc.s    e
    IL_0093:  call       void [mscorlib]System.Console::WriteLine(object)
    IL_0098:  nop
    IL_0099:  nop
    IL_009a:  leave.s    IL_009c

    IL_009c:  nop
    IL_009d:  ret
    IL_009e:  
    // Exception count 1
    .try IL_0001 to IL_008e catch [mscorlib]System.Exception handler IL_008e to IL_009c
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

} // end of class Alunos.Program

.class private auto ansi beforefieldinit Alunos.Aluno
       extends [mscorlib]System.Object
{
  .field public int32 number
  .field public string name
  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    // Code size       21 (0x15)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [mscorlib]System.Object::.ctor()
    IL_0006:  nop
    IL_0007:  nop
    IL_0008:  ldarg.0
    IL_0009:  ldstr      "AVE"
    IL_000e:  stfld      string Alunos.Aluno::name
    IL_0013:  nop
    IL_0014:  ret
  } // end of method Aluno::.ctor

  .method public hidebysig specialname rtspecialname 
          instance void  .ctor(int32 nr,
                               string name) cil managed
  {
    // Code size       24 (0x18)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [mscorlib]System.Object::.ctor()
    IL_0006:  nop
    IL_0007:  nop
    IL_0008:  ldarg.0
    IL_0009:  ldarg.1
    IL_000a:  stfld      int32 Alunos.Aluno::number
    IL_000f:  ldarg.0
    IL_0010:  ldarg.2
    IL_0011:  stfld      string Alunos.Aluno::name
    IL_0016:  nop
    IL_0017:  ret
  } // end of method Aluno::.ctor

  .method public hidebysig instance string 
          GetName() cil managed
  {
    // Code size       12 (0xc)
    .maxstack  1
    .locals init ([0] string CS$1$0000)
    IL_0000:  nop
    IL_0001:  ldarg.0
    IL_0002:  ldfld      string Alunos.Aluno::name
    IL_0007:  stloc.0
    IL_0008:  br.s       IL_000a

    IL_000a:  ldloc.0
    IL_000b:  ret
  } // end of method Aluno::GetName

  .method public hidebysig instance int32 
          GetNumber() cil managed
  {
    // Code size       12 (0xc)
    .maxstack  1
    .locals init ([0] int32 CS$1$0000)
    IL_0000:  nop
    IL_0001:  ldarg.0
    IL_0002:  ldfld      int32 Alunos.Aluno::number
    IL_0007:  stloc.0
    IL_0008:  br.s       IL_000a

    IL_000a:  ldloc.0
    IL_000b:  ret
  } // end of method Aluno::GetNumber

} // end of class Alunos.Aluno


// =============================================================

// *********** DISASSEMBLY COMPLETE ***********************
// WARNING: Created Win32 resource file D:\work\AVE2011\ExerciciosCSharp\Reflection\Reflection\bin\Debug\xpto.res
