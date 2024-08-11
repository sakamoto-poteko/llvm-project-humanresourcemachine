//===- HRMMachineFunctionInfo.cpp - HRM machine func info -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "HRMMachineFunctionInfo.h"

using namespace llvm;

void HRMFunctionInfo::anchor() { }

MachineFunctionInfo *
HRMFunctionInfo::clone(BumpPtrAllocator &Allocator, MachineFunction &DestMF,
    const DenseMap<MachineBasicBlock *, MachineBasicBlock *>
        &Src2DstMBB) const
{
    return DestMF.cloneInfo<HRMFunctionInfo>(*this);
}
