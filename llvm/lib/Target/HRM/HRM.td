//===-- HRM.td - Describe the HRM Target Machine ----------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===---------------------------------------------------------------------===//
// This is the top level entry point for the HRM target.
//===---------------------------------------------------------------------===//

//===---------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===---------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===---------------------------------------------------------------------===//
// Register File Description
//===---------------------------------------------------------------------===//

include "HRMRegisterInfo.td"

//===---------------------------------------------------------------------===//
// Instruction Descriptions
//===---------------------------------------------------------------------===//

include "HRMInstrInfo.td"

def HRMInstrInfo : InstrInfo;

//===---------------------------------------------------------------------===//
// Calling Conventions
//===---------------------------------------------------------------------===//

include "HRMCallingConv.td"

//===---------------------------------------------------------------------===//
// Assembly Printers
//===---------------------------------------------------------------------===//

def HRMAsmWriter : AsmWriter {
  string AsmWriterClassName = "InstPrinter";
  bit isMCAsmWriter = 1;
}

//===---------------------------------------------------------------------===//
// Assembly Parsers
//===---------------------------------------------------------------------===//

def HRMAsmParser : AsmParser {
  let ShouldEmitMatchRegisterName = 1;
  let ShouldEmitMatchRegisterAltName = 1;
}

def HRMAsmParserVariant : AsmParserVariant {
  int Variant = 0;

  // Recognize hard coded registers.
  string RegisterPrefix = "$";
  string TokenizingCharacters = "+";
}

//===---------------------------------------------------------------------===//
// Target Declaration
//===---------------------------------------------------------------------===//

def HRM : Target {
  let InstructionSet = HRMInstrInfo;
  let AssemblyWriters = [HRMAsmWriter];

  let AssemblyParsers = [HRMAsmParser];
  let AssemblyParserVariants = [HRMAsmParserVariant];
}
