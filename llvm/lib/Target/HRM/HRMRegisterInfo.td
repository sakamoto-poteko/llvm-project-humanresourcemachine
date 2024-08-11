//===-- HRMRegisterInfo.td - HRM Register defs -------------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the HRM register file
//===----------------------------------------------------------------------===//

class HRMReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "HRM";
}

def R0 : HRMReg<0, "r0">;

def GPReg : RegisterClass<"HRM", [i16], 16, (add R0)>;
