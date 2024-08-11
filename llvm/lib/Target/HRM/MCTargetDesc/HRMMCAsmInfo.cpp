//===-- HRMMCAsmInfo.cpp - HRM Asm Properties -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the HRMMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "HRMMCAsmInfo.h"

#include "llvm/BinaryFormat/Dwarf.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void HRMMCAsmInfo::anchor() { }

HRMMCAsmInfo::HRMMCAsmInfo(const Triple &TheTriple) {
  // This architecture is little endian only
  IsLittleEndian = false;

  AlignmentIsInBytes          = false;
  Data16bitsDirective         = "\t.word\t";
  Data32bitsDirective         = "\t.dword\t";
  Data64bitsDirective         = "\t.qword\t";

  PrivateGlobalPrefix         = ".L";
  PrivateLabelPrefix          = ".L";

  LabelSuffix                 = ":";

  CommentString               = ";";

  ZeroDirective               = "\t.zero\t";

  UseAssignmentForEHBegin     = true;

  SupportsDebugInformation    = true;
  ExceptionsType              = ExceptionHandling::DwarfCFI;
  DwarfRegNumForCFI           = true;
}