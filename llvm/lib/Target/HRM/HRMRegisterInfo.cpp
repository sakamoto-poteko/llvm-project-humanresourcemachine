//===-- HRMRegisterInfo.cpp - HRM Register Information --------------------===//
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

#include "HRMRegisterInfo.h"
#include "HRMFrameLowering.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"

#include "HRM.h"
#include "HRMInstrInfo.h"
#include "MCTargetDesc/HRMMCTargetDesc.h"

#define GET_REGINFO_TARGET_DESC
#include "HRMGenRegisterInfo.inc"

namespace llvm {

HRMRegisterInfo::HRMRegisterInfo()
    : HRMGenRegisterInfo(0)
{
}

const MCPhysReg *HRMRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const
{
    // no callee saved regs
    return nullptr;
}

BitVector HRMRegisterInfo::getReservedRegs(const MachineFunction &MF) const
{
    // no reserved regs
    return BitVector();
}

bool HRMRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const
{
    return true;
}

bool HRMRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj, unsigned FIOperandNum, RegScavenger *RS) const
{
    // assert(SPAdj == 0 && "Unexpected SPAdj value");

    MachineInstr &MI = *II;
    int FrameIndex = MI.getOperand(FIOperandNum).getIndex();

    // Fetch the machine function and the frame information
    MachineFunction &MF = *MI.getParent()->getParent();
    const MachineFrameInfo &MFI = MF.getFrameInfo();

    // Directly calculate the memory address for the frame index
    int Offset = MFI.getObjectOffset(FrameIndex);

    // Replace the frame index operand with the calculated memory address
    MI.getOperand(FIOperandNum).ChangeToImmediate(Offset);

    // If the instruction is a load or store, we may need to handle addressing
    if (MI.mayLoadOrStore()) {
        // For load/store, set up the correct addressing mode
        // Direct addressing: load/store r0, [address]
        // Indirect addressing: load/store r0, [address_stored_in_address]

        // For now let's support direct only
        MI.getOperand(FIOperandNum).ChangeToImmediate(Offset);

        // Example: Replace the operand with a memory address
        // Here, we assume the architecture's instruction expects direct or indirect address
        // if (/* Direct Addressing Mode */) {
        // Simply set the memory address
        // MI.getOperand(FIOperandNum).ChangeToImmediate(Offset);
        // } else if (/* Indirect Addressing Mode */) {
        // Assuming the offset points to an address that contains the real address
        // This would require fetching that address and using it
        // Indirect addressing might be modeled as `load r0, [address]`
        // MI.getOperand(FIOperandNum).ChangeToMemoryAddress(Offset);
        // }
    }

    // Return false to indicate that the instruction was modified in place
    return false;
}

Register HRMRegisterInfo::getFrameRegister(const MachineFunction &MF) const
{
    llvm_unreachable("This architecture does not use a frame register");
    return Register(); // Or use a specific invalid register value if defined
}

} // end of namespace llvm
