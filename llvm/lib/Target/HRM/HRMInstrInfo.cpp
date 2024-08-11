//===-- HRMInstrInfo.cpp - HRM Instruction Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the HRM implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "HRMInstrInfo.h"
#include "HRM.h"
#include "HRMMachineFunctionInfo.h"
// #include "MCTargetDesc/HRMBaseInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "HRMGenInstrInfo.inc"

using namespace llvm;

// Pin the vtable to this file.
void HRMInstrInfo::anchor() {}

HRMInstrInfo::HRMInstrInfo()
  : HRMGenInstrInfo(HRM::ADJCALLSTACKDOWN, HRM::ADJCALLSTACKUP), RI() {
}
