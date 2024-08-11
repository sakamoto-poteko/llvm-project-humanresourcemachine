//===- HRMMachineFunctionInfo.h - HRM machine function info -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares HRM-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_HRM_HRMMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_HRM_HRMMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"
#include <vector>

namespace llvm {

/// HRMFunctionInfo - This class is derived from MachineFunction private
/// HRM target-specific information for each MachineFunction.
class HRMFunctionInfo : public MachineFunctionInfo {
    virtual void anchor();

public:
    explicit HRMFunctionInfo(const Function &F, const TargetSubtargetInfo *STI)
    {
    }

    virtual ~HRMFunctionInfo() { }

    MachineFunctionInfo *
    clone(BumpPtrAllocator &Allocator, MachineFunction &DestMF,
        const DenseMap<MachineBasicBlock *, MachineBasicBlock *> &Src2DstMBB)
        const override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_HRM_HRMMACHINEFUNCTIONINFO_H
