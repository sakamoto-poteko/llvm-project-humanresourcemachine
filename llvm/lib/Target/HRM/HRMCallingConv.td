//===- HRMCallingConv.td - Calling Conventions for HRM -*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for HRM architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// HRM Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_HRM : CallingConv<[
  // i16 values are returned in register r0.
  CCIfType<[i16], CCAssignToReg<[R0]>>
]>;

//===----------------------------------------------------------------------===//
// HRM Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_HRM : CallingConv<[
  // The first i16 argument is passed in r0.
  CCIfType<[i16], CCAssignToReg<[R0]>>,

  // Subsequent i16 values get stored in stack slots that are 2 bytes in
  // size and 2-byte aligned.
  CCIfType<[i16], CCAssignToStack<2, 2>>
]>;
