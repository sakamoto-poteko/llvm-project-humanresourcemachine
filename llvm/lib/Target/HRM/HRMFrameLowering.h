//===- HRMFrameLowering.h - Define frame lowering for HRM -------*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_HRM_HRMFRAMELOWERING_H
#define LLVM_LIB_TARGET_HRM_HRMFRAMELOWERING_H

#include "HRM.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class MachineFunction;
class HRMSubtarget;
class HRMInstrInfo;

class HRMFrameLowering : public TargetFrameLowering {
public:
    HRMFrameLowering(const HRMSubtarget &st)
        : TargetFrameLowering(TargetFrameLowering::StackGrowsUp, Align(2), 0)
    {
    }

    void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
    void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
    MachineBasicBlock::iterator eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB, MachineBasicBlock::iterator MI) const override;
};

}
#endif