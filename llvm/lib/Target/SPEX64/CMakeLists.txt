add_llvm_target(SPEX64CodeGen
  SPEX64TargetMachine.cpp
  SPEX64TargetMachineImpl.cpp
  SPEX64TargetInfo.cpp
  SPEX64MCTargetDesc.cpp
)

add_custom_target(SPEX64 DEPENDS LLVMSPEX64CodeGen)