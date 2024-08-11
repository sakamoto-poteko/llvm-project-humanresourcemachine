//===-- HRMInstrInfo.h - HRM Instruction Information --------*- C++ -*-===//
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

#ifndef HRMINSTRUCTIONINFO_H
#define HRMINSTRUCTIONINFO_H

#include "HRMRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"

#define GET_INSTRINFO_HEADER
#include "HRMGenInstrInfo.inc"

namespace llvm {

class HRMInstrInfo : public HRMGenInstrInfo {
    const HRMRegisterInfo RI;
    virtual void anchor();

public:
    HRMInstrInfo();
    virtual ~HRMInstrInfo() { }
    // leave it blank for now
};
}

#endif