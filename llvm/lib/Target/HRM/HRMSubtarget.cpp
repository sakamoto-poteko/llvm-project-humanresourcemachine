//===-- HRMSubtarget.cpp - HRM Subtarget Information ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the HRM specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "HRMSubtarget.h"

#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/TargetRegistry.h"

#include "HRM.h"
#include "HRMTargetMachine.h"
#include "MCTargetDesc/HRMMCTargetDesc.h"

#define DEBUG_TYPE "HRM-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "HRMGenSubtargetInfo.inc"

namespace llvm {

HRMSubtarget::HRMSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const HRMTargetMachine &TM)
    : HRMGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS), InstrInfo(*this),
      TLInfo(TM, initializeSubtargetDependencies(CPU, FS, TM)) {
  // Parse features string.
  ParseSubtargetFeatures(CPU, /*TuneCPU*/ CPU, FS);
}

HRMSubtarget &
HRMSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS,
                                              const TargetMachine &TM) {
  // Parse features string.
  ParseSubtargetFeatures(CPU, /*TuneCPU*/ CPU, FS);
  return *this;
}

} // end of namespace llvm
