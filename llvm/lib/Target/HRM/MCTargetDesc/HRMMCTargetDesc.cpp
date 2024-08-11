//===-- HRMMCTargetDesc.cpp - HRM Target Descriptions -----------------===//
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

#include "HRMMCTargetDesc.h"
#include "HRMInstPrinter.h"
#include "HRMMCAsmInfo.h"
#include "HRMTargetStreamer.h"

#include "TargetInfo/HRMTargetInfo.h"

#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "HRMGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "HRMGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "HRMGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createHRMMCInstrInfo() {
    MCInstrInfo *X = new MCInstrInfo();
    InitHRMMCInstrInfo(X);
    return X;
}

static MCRegisterInfo *createHRMMCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitHRMMCRegisterInfo(X, HRM::GPReg);
    return X;
}

static MCSubtargetInfo *createHRMMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
    return createHRMMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

static MCAsmInfo *createHRMMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
    // TODO: set initial stack state here
    return new HRMMCAsmInfo(TT);
}

static MCInstPrinter *createHRMMCInstPrinter(const Triple &TT,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
    return new HRMInstPrinter(MAI, MII, MRI);
}

HRMTargetStreamer::HRMTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
HRMTargetStreamer::~HRMTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint) {
    return new HRMTargetStreamer(S);
}

// Force static initialization.
extern "C" void LLVMInitializeHRMTargetMC() {
    Target &TheHRMTarget = getTheHRMTarget();
    RegisterMCAsmInfoFn X(TheHRMTarget, createHRMMCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(TheHRMTarget, createHRMMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(TheHRMTarget, createHRMMCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(TheHRMTarget,
                                            createHRMMCSubtargetInfo);

    // Register the MCInstPrinter
    TargetRegistry::RegisterMCInstPrinter(TheHRMTarget, createHRMMCInstPrinter);

    TargetRegistry::RegisterAsmTargetStreamer(TheHRMTarget,
                                              createTargetAsmStreamer);

    // Register the MCInstPrinter
    TargetRegistry::RegisterMCInstPrinter(TheHRMTarget, createHRMMCInstPrinter);

    //   // Register the ASM Backend.
    //   TargetRegistry::RegisterMCAsmBackend(TheHRMTarget,
    //   createHRMAsmBackend);

    //   // Register the MCCodeEmitter
    //   TargetRegistry::RegisterMCCodeEmitter(TheHRMTarget,
    //   createHRMMCCodeEmitter);
}