//===-- HRMTargetMachine.h - Define TargetMachine for HRM -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the HRM specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HRM_TARGET_MACHINE_H
#define LLVM_HRM_TARGET_MACHINE_H

#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#include "HRMFrameLowering.h"
#include "HRMISelLowering.h"
#include "HRMInstrInfo.h"
#include "HRMSelectionDAGInfo.h"
#include "HRMSubtarget.h" //

#include <optional>

namespace llvm {

class HRMTargetMachine : public LLVMTargetMachine {
public:
  HRMTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                   bool JIT);

  const HRMSubtarget *getSubtargetImpl() const { return &SubTarget; }
  const HRMSubtarget *getSubtargetImpl(const Function &) const override { return &SubTarget; };

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return this->TLOF.get();
  }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  MachineFunctionInfo *
  createMachineFunctionInfo(BumpPtrAllocator &Allocator, const Function &F,
                            const TargetSubtargetInfo *STI) const override;

  bool isNoopAddrSpaceCast(unsigned SrcAs, unsigned DestAs) const override {
    // While HRM has different address spaces, they are all represented by
    // 16-bit pointers that can be freely casted between (of course, a pointer
    // must be cast back to its original address space to be dereferenceable).
    // To be safe, also check the pointer size in case we implement __memx
    // pointers.
    return getPointerSize(SrcAs) == getPointerSize(DestAs);
  }

private:
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  HRMSubtarget SubTarget;
};

} // end namespace llvm

#endif // LLVM_HRM_TARGET_MACHINE_H
