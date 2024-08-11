//===-- HRMMCAsmInfo.h - HRM Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the HRMMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_HRM_MCTARGETDESC_HRMMCASMINFO_H
#define LLVM_LIB_TARGET_HRM_MCTARGETDESC_HRMMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class HRMMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit HRMMCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_HRM_MCTARGETDESC_HRMMCASMINFO_H