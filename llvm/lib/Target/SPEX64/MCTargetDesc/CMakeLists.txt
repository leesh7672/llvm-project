add_llvm_library(LLVMSPEX64Desc
  SPEX64MCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  Support
  TargetParser
)
