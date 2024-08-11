//===-- HRMTargetMachine.cpp - Define TargetMachine for HRM ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the HRM specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#include "HRMTargetMachine.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"

#include "HRM.h"
#include "HRMMachineFunctionInfo.h"
#include "HRMTargetObjectFile.h"
#include "MCTargetDesc/HRMMCTargetDesc.h"
#include "TargetInfo/HRMTargetInfo.h"

#include <optional>

namespace llvm {

static const char *HRMDataLayout =
    "e-m:e-p:16:16-i16:16:16-a:16:16-n16";

/// Processes a CPU name.
static StringRef getCPU(StringRef CPU) {
  if (CPU.empty() || CPU == "generic") {
    return "HRM";
  }

  return CPU;
}

HRMTargetMachine::HRMTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, HRMDataLayout, TT, getCPU(CPU), FS, Options,
                        RM, CM, OL),
      SubTarget(TT, std::string(getCPU(CPU)), std::string(FS), *this) {
  this->TLOF = std::make_unique<HRMTargetObjectFile>();
  initAsmInfo();
}

namespace {
/// HRM Code Generator Pass Configuration Options.
class HRMPassConfig : public TargetPassConfig {
public:
  HRMPassConfig(HRMTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  HRMTargetMachine &getHRMTargetMachine() const {
    return getTM<HRMTargetMachine>();
  }

  void addIRPasses() override;
  bool addInstSelector() override;
  bool addPreISel() override;
  void addPreSched2() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *HRMTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new HRMPassConfig(*this, PM);
}

bool HRMPassConfig::addPreISel() { return false; }

void HRMPassConfig::addIRPasses() { TargetPassConfig::addIRPasses(); }

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeHRMTarget() {
  // Register the target.
  RegisterTargetMachine<HRMTargetMachine> X(getTheHRMTarget());
}

MachineFunctionInfo *HRMTargetMachine::createMachineFunctionInfo(
    BumpPtrAllocator &Allocator, const Function &F,
    const TargetSubtargetInfo *STI) const {
  return HRMMachineFunctionInfo::create<HRMMachineFunctionInfo>(Allocator, F,
                                                                STI);
}

//===----------------------------------------------------------------------===//
// Pass Pipeline Configuration
//===----------------------------------------------------------------------===//

bool HRMPassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createHRMISelDag(getHRMTargetMachine(), getOptLevel()));

  return false;
}

void HRMPassConfig::addPreSched2() {
  addPass(createHRMExpandPseudoPass());
}

void HRMPassConfig::addPreEmitPass() {
  // Must run branch selection immediately preceding the asm printer.
  // addPass(&BranchRelaxationPassID);
}

} // end of namespace llvm
