//===-- HRM.h - Top-level interface for HRM representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// HRM back-end.
//
//===----------------------------------------------------------------------===//

#ifndef TARGET_HRM_H
#define TARGET_HRM_H

#include "MCTargetDesc/HRMMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class HRMTargetMachine;
class FunctionPass;
class PassRegistry;

FunctionPass *createHRMISelDag(HRMTargetMachine &TM, CodeGenOptLevel OptLevel);
} // end namespace llvm;

#endif