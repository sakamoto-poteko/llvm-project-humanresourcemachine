//===- HRMInstPrinter.cpp - HRM MCInst to assembly syntax -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an HRM MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "HRMInstPrinter.h"
// #include "MCTargetDesc/HRMInfo.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#include "HRMGenAsmWriter.inc"

// template <class T>
// static const char *BadConditionCode(T cc) {
//   LLVM_DEBUG(dbgs() << "Unknown condition code passed: " << cc << "\n");
//   return "{unknown-cc}";
// }

// static const char *HRMBRCondCodeToString(HRMCC::BRCondCode BRCC) {
//   switch (BRCC) {
//   case HRMCC::BREQ:
//     return "eq";
//   case HRMCC::BRNE:
//     return "ne";
//   case HRMCC::BRLT:
//     return "lt";
//   case HRMCC::BRGE:
//     return "ge";
//   case HRMCC::BRLO:
//     return "lo";
//   case HRMCC::BRHS:
//     return "hs";
//   }
//   return BadConditionCode(BRCC);
// }

// static const char *HRMCondCodeToString(HRMCC::CondCode CC) {
//   switch (CC) {
//   case HRMCC::EQ:
//     return "eq";
//   case HRMCC::NE:
//     return "ne";
//   case HRMCC::P:
//     return "p";
//   case HRMCC::N:
//     return "n";
//   case HRMCC::HS:
//     return "hs";
//   case HRMCC::LO:
//     return "lo";
//   case HRMCC::GT:
//     return "gt";
//   case HRMCC::GE:
//     return "ge";
//   case HRMCC::VS:
//     return "vs";
//   case HRMCC::VC:
//     return "vc";
//   case HRMCC::LT:
//     return "lt";
//   case HRMCC::LE:
//     return "le";
//   case HRMCC::HI:
//     return "hi";
//   case HRMCC::LS:
//     return "ls";
//   case HRMCC::PNZ:
//     return "pnz";
//   case HRMCC::AL:
//     return "al";
//   case HRMCC::NZ:
//     return "nz";
//   case HRMCC::Z:
//     return "z";
//   }
//   return BadConditionCode(CC);
// }

// void HRMInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) const {
//   OS << StringRef(getRegisterName(Reg)).lower();
// }

void HRMInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                               StringRef Annot, const MCSubtargetInfo &STI,
                               raw_ostream &O) {
    printInstruction(MI, Address, O);
    printAnnotation(O, Annot);
}

// static void printExpr(const MCExpr *Expr, const MCAsmInfo *MAI,
//                       raw_ostream &OS) {
//   int Offset = 0;
//   const MCSymbolRefExpr *SRE;

//   if (const auto *CE = dyn_cast<MCConstantExpr>(Expr)) {
//     OS << "0x";
//     OS.write_hex(CE->getValue());
//     return;
//   }

//   if (const auto *BE = dyn_cast<MCBinaryExpr>(Expr)) {
//     SRE = dyn_cast<MCSymbolRefExpr>(BE->getLHS());
//     const auto *CE = dyn_cast<MCConstantExpr>(BE->getRHS());
//     assert(SRE && CE && "Binary expression must be sym+const.");
//     Offset = CE->getValue();
//   } else {
//     SRE = dyn_cast<MCSymbolRefExpr>(Expr);
//     assert(SRE && "Unexpected MCExpr type.");
//   }
//   assert(SRE->getKind() == MCSymbolRefExpr::VK_None);

//   // Symbols are prefixed with '@'
//   OS << '@';
//   SRE->getSymbol().print(OS, MAI);

//   if (Offset) {
//     if (Offset > 0)
//       OS << '+';
//     OS << Offset;
//   }
// }

void HRMInstPrinter::printOperand(const MCInst *MI, unsigned OpNum,
                                  raw_ostream &O) {
    const MCOperand &Op = MI->getOperand(OpNum);
    if (Op.isReg()) {
        printRegName(O, Op.getReg());
        return;
    }

    if (Op.isImm()) {
        O << Op.getImm();
        return;
    }

    assert(!Op.isExpr()); // It cannot be expr. We don't support it.
    //   assert(Op.isExpr() && "unknown operand kind in printOperand");
    //   printExpr(Op.getExpr(), &MAI, O);
}

// void HRMInstPrinter::printMemOperandRI(const MCInst *MI, unsigned OpNum,
//                                        raw_ostream &O) {
//   const MCOperand &base = MI->getOperand(OpNum);
//   const MCOperand &offset = MI->getOperand(OpNum + 1);
//   assert(base.isReg() && "Base should be register.");
//   assert(offset.isImm() && "Offset should be immediate.");
//   printRegName(O, base.getReg());
//   O << "," << offset.getImm();
// }

// void HRMInstPrinter::printPredicateOperand(const MCInst *MI, unsigned OpNum,
//                                            raw_ostream &O) {

//   const MCOperand &Op = MI->getOperand(OpNum);
//   assert(Op.isImm() && "Predicate operand is immediate.");
//   O << HRMCondCodeToString((HRMCC::CondCode)Op.getImm());
// }

// void HRMInstPrinter::printBRCCPredicateOperand(const MCInst *MI, unsigned
// OpNum,
//                                                raw_ostream &O) {
//   const MCOperand &Op = MI->getOperand(OpNum);
//   assert(Op.isImm() && "Predicate operand is immediate.");
//   O << HRMBRCondCodeToString((HRMCC::BRCondCode)Op.getImm());
// }

// void HRMInstPrinter::printCCOperand(const MCInst *MI, int OpNum,
//                                     raw_ostream &O) {
//   O << HRMCondCodeToString((HRMCC::CondCode)MI->getOperand(OpNum).getImm());
// }

// void HRMInstPrinter::printU6ShiftedBy(unsigned ShiftBy, const MCInst *MI,
//                                       int OpNum, raw_ostream &O) {
//   const MCOperand &MO = MI->getOperand(OpNum);
//   if (MO.isImm()) {
//     unsigned Value = MO.getImm();
//     unsigned Value2 = Value >> ShiftBy;
//     if (Value2 > 0x3F || (Value2 << ShiftBy != Value)) {
//       errs() << "!!! Instruction has out-of-range U6 immediate operand:\n"
//              << "    Opcode is " << MI->getOpcode() << "; operand value is "
//              << Value;
//       if (ShiftBy)
//         errs() << " scaled by " << (1 << ShiftBy) << "\n";
//       assert(false && "instruction has wrong format");
//     }
//   }
//   printOperand(MI, OpNum, O);
// }

// void HRMInstPrinter::printU6(const MCInst *MI, int OpNum, raw_ostream &O) {
//   printU6ShiftedBy(0, MI, OpNum, O);
// }
