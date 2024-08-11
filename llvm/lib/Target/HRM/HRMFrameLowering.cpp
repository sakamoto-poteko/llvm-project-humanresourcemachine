//===- HRMFrameLowering.cpp - Define frame lowering for HRM -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class implements the HRM specific frame lowering.
//
//===----------------------------------------------------------------------===//

#include "HRMFrameLowering.h"
#include "HRMMachineFunctionInfo.h"
#include "HRMSubtarget.h"

#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

// For now let's do nothing.
void HRMFrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const
{
    LLVM_DEBUG(dbgs() << "Emit Prologue: " << MF.getName() << "\n");
}

void llvm::HRMFrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const
{
    LLVM_DEBUG(dbgs() << "Emit Epilogue: " << MF.getName() << "\n");
}

MachineBasicBlock::iterator llvm::HRMFrameLowering::eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB, MachineBasicBlock::iterator MI) const
{
    llvm_unreachable("Call Frame Pseudo Instructions do not exist on this target!");
}
