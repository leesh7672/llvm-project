#include "SPEX64TargetInfo.h"

using namespace llvm;

extern "C" void LLVMInitializeSPEX64TargetMC() {
  (void)getTheSPEX64Target();
}
