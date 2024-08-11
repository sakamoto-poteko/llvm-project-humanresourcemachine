add_llvm_component_library(LLVMHRMDesc
  # HRMAsmBackend.cpp
  # HRMELFObjectWriter.cpp
  # HRMELFStreamer.cpp
  HRMInstPrinter.cpp
  HRMMCAsmInfo.cpp
  # HRMMCCodeEmitter.cpp
  # HRMMCELFStreamer.cpp
  # HRMMCExpr.cpp
  HRMMCTargetDesc.cpp
  # HRMTargetStreamer.cpp

  LINK_COMPONENTS
  HRMInfo
  CodeGenTypes
  MC
  Support
  TargetParser

  ADD_TO_COMPONENT
  HRM
)

add_dependencies(LLVMHRMDesc HRMCommonTableGen)

