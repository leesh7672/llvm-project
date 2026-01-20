add_llvm_library(LLVMSPEX64Desc
  SPEX64MCTargetDesc.cpp
  SPEX64MCCodeEmitter.cpp
  SPEX64AsmBackend.cpp
  SPEX64ELFObjectWriter.cpp
  SPEX64MCAsmInfo.cpp

  DEPENDS
  SPEX64CommonTableGen

  LINK_COMPONENTS
  MC
  Support
  TargetParser
)
