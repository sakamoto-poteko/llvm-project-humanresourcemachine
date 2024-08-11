//===-- HRMTargetInfo.cpp - HRM Target Implementation ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/HRMTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
namespace llvm {
Target &getTheHRMTarget() {
  static Target TheHRMTarget;
  return TheHRMTarget;
}
} // namespace llvm

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeHRMTargetInfo() {
  llvm::RegisterTarget<llvm::Triple::hrm> X(llvm::getTheHRMTarget(), "hrm",
                                            "Human Resource Machine", "HRM");
}
