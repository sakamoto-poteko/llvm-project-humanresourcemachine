//===-- HRMInstrInfo.td - HRM Instruction Information -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// Include the HRM Instruction Formats
include "HRMInstrFormats.td"

// Define the ALU instructions
let mayLoad = 1, mayStore = 0 in {
  def ADD : ALUInst<0b0000, (outs GPReg:$dst), (ins GPReg:$src, i8imm:$addr), "ADD $addr", []>;
  def SUB : ALUInst<0b0001, (outs GPReg:$dst), (ins GPReg:$src, i8imm:$addr), "SUB $addr", []>;
  def BUMPUP : ALUInst<0b0010, (outs GPReg:$dst), (ins GPReg:$src, i8imm:$addr), "BUMPUP $addr", []>;
  def BUMPDOWN : ALUInst<0b0011, (outs GPReg:$dst), (ins GPReg:$src, i8imm:$addr), "BUMPDN $addr", []>;
}

// Define the branch instructions
let isBranch = 1, isTerminator = 1, isBarrier = 1 in {
  def JUMP : BranchInst<0b0100, (outs), (ins b_target:$addr), "JUMP $addr", []>;
  def JUMPZ : BranchInst<0b0101, (outs), (ins b_target:$addr), "JUMPZ $addr", []>;
  def JUMPN : BranchInst<0b0110, (outs), (ins b_target:$addr), "JUMPN $addr", []>;
}

// Define the memory operations
let mayLoad = 1, mayStore = 0 in {
  def COPYFROM : MemInstDirect<0b1000, (outs GPReg:$dst), (ins i8imm:$addr), "COPYFROM $addr", []>;
  def COPYFROM_INDIRECT : MemInstIndirect<0b1000, (outs GPReg:$dst), (ins i8imm:$addr), "COPYFROM [$addr]", []>;
}

let mayStore = 1, mayLoad = 0 in {
  def COPYTO : MemInstDirect<0b1001, (outs), (ins GPReg:$src, i8imm:$addr), "COPYTO $addr", []>;
  def COPYTO_INDIRECT : MemInstIndirect<0b1001, (outs), (ins GPReg:$src, i8imm:$addr), "COPYTO [$addr]", []>;
}

// Define the I/O operations
def INBOX : IOInst<0b1010, (outs GPReg:$dst), (ins), "INBOX", []> {
  let mayLoad = 1;
  let mayStore = 0;
}

def OUTBOX : IOInst<0b1011, (outs), (ins GPReg:$src), "OUTBOX", []> {
  let mayStore = 1;
  let mayLoad = 0;
}

// Stack
// def ADJCALLSTACKDOWN : HRMPseudoInst<(outs), (ins i16imm:$amt), "# ADJCALLSTACKDOWN $amt", [(callseq_start timm:$amt)]>;
// def ADJCALLSTACKUP   : HRMPseudoInst<(outs), (ins i16imm:$amt1, i16imm:$amt2), "# ADJCALLSTACKUP $amt1", [(callseq_end timm:$amt1, timm:$amt2)]>;

// it supports no call stack but LLVM asks for it
def ADJCALLSTACKDOWN : HRMPseudoInst<(outs), (ins), "# ADJCALLSTACKDOWN", []>;
def ADJCALLSTACKUP   : HRMPseudoInst<(outs), (ins), "# ADJCALLSTACKUP", []>;
