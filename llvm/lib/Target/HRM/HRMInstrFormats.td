//===-- HRMInstrFormats.td - HRM Instruction Formats -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// Define basic instruction format classes

// Base class for all HRM instructions
class InstHRM<dag outs, dag ins, string asmstr, list<dag> pattern>
    : Instruction {
  field bits<16> Inst; // 16-bit instructions

  let Namespace = "HRM";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
  let Size = 2; // 16 bits = 2 bytes
}

// Format for instructions with ALU operations like add, sub, bump+, bump-
class ALUInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstHRM<outs, ins, asmstr, pattern> {
  let Inst{15-12} = opcode;  // 4-bit opcode
}

// Format for branch instructions like jump, jumpz, jumpn
class BranchInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstHRM<outs, ins, asmstr, pattern> {
  bits<8> addr;
  let Inst{15-12} = opcode;  // 4-bit opcode for branching
  let Inst{7-0} = addr;       // 8-bit immediate value for branch target
}

// Format for memory operations like copyfrom, copyto
class MemInstDirect<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstHRM<outs, ins, asmstr, pattern> {
  bits<8> addr;
  let Inst{15-12} = opcode;  // 4-bit opcode for memory operations
  let Inst{11} = 0;
  let Inst{7-0} = addr;     // 8-bit address value or indirect address
}

class MemInstIndirect<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstHRM<outs, ins, asmstr, pattern> {
  bits<8> addr;
  let Inst{15-12} = opcode;  // 4-bit opcode for memory operations
  let Inst{11} = 1;
  let Inst{7-0} = addr;     // 8-bit address value or indirect address
}

// Format for I/O operations like inbox and outbox
class IOInst<bits<4> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstHRM<outs, ins, asmstr, pattern> {
  let Inst{15-12} = opcode;  // 4-bit opcode for I/O operations
}

// pseudo instructions format
class HRMPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
    : InstHRM<outs, ins, asmstr, pattern> {
  let isPseudo = 1;
}


def SDT_HRMCallSeqStart : SDCallSeqStart<[ SDTCisVT<0, i8> ]>;

def SDT_HRMCallSeqEnd   : SDCallSeqEnd<[ SDTCisVT<0, i8>, SDTCisVT<1, i8> ]>;

def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_HRMCallSeqStart,
                           [SDNPHasChain, SDNPOutGlue]>;

def callseq_end   : SDNode<"ISD::CALLSEQ_END",   SDT_HRMCallSeqEnd,
                           [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def b_target : Operand<OtherVT>;
