#include "SPEX64TargetMachine.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"

using namespace llvm;

SPEX64TargetMachine::SPEX64TargetMachine(
    const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
    const TargetOptions &Options, std::optional<Reloc::Model> RM,
    std::optional<CodeModel::Model> CM, CodeGenOptLevel OL, bool JIT)
    : TargetMachine(T, "e-m:e-p:64:64-i64:64-n8:16:32:64-S128", TT, CPU, FS,
                    Options) {}

TargetPassConfig *SPEX64TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TargetPassConfig(*this, PM);
}
