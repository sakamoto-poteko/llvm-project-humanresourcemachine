add_llvm_component_group(HRM)

set(LLVM_TARGET_DEFINITIONS HRM.td)

# tablegen(LLVM HRMGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM HRMGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM HRMGenCallingConv.inc -gen-callingconv)
tablegen(LLVM HRMGenDAGISel.inc -gen-dag-isel)
# tablegen(LLVM HRMGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM HRMGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM HRMGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM HRMGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM HRMGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(HRMCommonTableGen)

add_llvm_target(HRMCodeGen
  HRMAsmPrinter.cpp
  # AVRExpandPseudoInsts.cpp
  HRMFrameLowering.cpp
  HRMInstrInfo.cpp
  HRMISelDAGToDAG.cpp
  HRMMachineFunctionInfo.cpp
  # AVRISelLowering.cpp
  # AVRMCInstLower.cpp
  HRMRegisterInfo.cpp
  # AVRShiftExpand.cpp
  HRMSubtarget.cpp
  HRMTargetMachine.cpp
  # AVRTargetObjectFile.cpp

  DEPENDS
  intrinsics_gen

  LINK_COMPONENTS
  HRMDesc
  HRMInfo
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  HRM
  )

# add_subdirectory(AsmParser)
# add_subdirectory(Disassembler)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
