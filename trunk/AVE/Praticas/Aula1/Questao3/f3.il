
//  Microsoft (R) .NET Framework IL Disassembler.  Version 4.0.30319.1
//  Copyright (c) Microsoft Corporation.  All rights reserved.



// Metadata version: v2.0.50727
.assembly extern mscorlib
{
  .publickeytoken = (B7 7A 5C 56 19 34 E0 89 )                         // .z\V.4..
  .ver 2:0:0:0
}
.module f3.dll
// MVID: {D61ACB7D-AF6A-42D3-A0D6-51AC5A88B2F9}
.imagebase 0x00400000
.file alignment 0x00000200
.stackreserve 0x00100000
.subsystem 0x0003       // WINDOWS_CUI
.corflags 0x00000001    //  ILONLY
// Image base: 0x001D0000


// =============== CLASS MEMBERS DECLARATION ===================

.class public auto ansi beforefieldinit C3
       extends [mscorlib]System.Object
{
  .field private int32 i
  .method public hidebysig instance int32 
          getInt() cil managed
  {
    // Code size       7 (0x7)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  ldfld      int32 C3::i
    IL_0006:  ret
  } // end of method C3::getInt

  .method public hidebysig instance void 
          saveInt(int32 i) cil managed
  {
    // Code size       8 (0x8)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  ldarg.1
    IL_0002:  stfld      int32 C3::i
    IL_0007:  ret
  } // end of method C3::saveInt

  .method public hidebysig specialname rtspecialname 
          instance void  .ctor() cil managed
  {
    // Code size       7 (0x7)
    .maxstack  8
    IL_0000:  ldarg.0
    IL_0001:  call       instance void [mscorlib]System.Object::.ctor()
    IL_0006:  ret
  } // end of method C3::.ctor

} // end of class C3


// =============================================================

.custom ([mscorlib]System.Runtime.CompilerServices.AssemblyAttributesGoHere) instance void [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::.ctor() = ( 01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
                                                                                                                                                                                63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01 )       // ceptionThrows.
// *********** DISASSEMBLY COMPLETE ***********************
