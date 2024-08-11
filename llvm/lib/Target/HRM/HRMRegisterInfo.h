//===-- HRMRegisterInfo.h - HRM Register Information Impl -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the HRM implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HRM_REGISTER_INFO_H
#define LLVM_HRM_REGISTER_INFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "HRMGenRegisterInfo.inc"

namespace llvm {

/// Utilities relating to HRM registers.
class HRMRegisterInfo : public HRMGenRegisterInfo {
public:
    HRMRegisterInfo();

public:
    /// Code Generation virtual methods...

    const MCPhysReg *
    getCalleeSavedRegs(const MachineFunction *MF) const override;

    BitVector getReservedRegs(const MachineFunction &MF) const override;

    bool requiresRegisterScavenging(const MachineFunction &MF) const override;

    bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj, unsigned FIOperandNum, RegScavenger *RS = nullptr) const override;

    Register getFrameRegister(const MachineFunction &MF) const override;
};

} // end namespace llvm

#endif // LLVM_HRM_REGISTER_INFO_H
