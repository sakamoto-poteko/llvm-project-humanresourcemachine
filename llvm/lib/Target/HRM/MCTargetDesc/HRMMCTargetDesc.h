//===-- HRMMCTargetDesc.h - HRM Target Descriptions ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides HRM specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef HRMMCTARGETDESC_H
#define HRMMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class Target;
class MCInstrInfo;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCContext;
class MCCodeEmitter;
class MCAsmInfo;
class MCCodeGenInfo;
class MCInstPrinter;
class MCObjectWriter;
class MCAsmBackend;

class StringRef;
class raw_ostream;
class raw_pwrite_stream;
class Triple;

extern Target TheHRMTarget;

MCCodeEmitter *createHRMMCCodeEmitter(const MCInstrInfo &MCII,
                                      const MCRegisterInfo &MRI,
                                      MCContext &Ctx);

MCAsmBackend *createHRMAsmBackend(const Target &T, const MCRegisterInfo &MRI,
                                  const Triple &TT, StringRef CPU);

MCObjectWriter *createHRMELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI);

} // End llvm namespace

// Defines symbolic names for HRM registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "HRMGenRegisterInfo.inc"

// Defines symbolic names for the HRM instructions.
//
#define GET_INSTRINFO_ENUM
#include "HRMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "HRMGenSubtargetInfo.inc"

#endif