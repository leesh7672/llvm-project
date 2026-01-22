#include "SPEX64AsmPrinter.h"
#include "TargetInfo/SPEX64TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

SPEX64AsmPrinter::SPEX64AsmPrinter(TargetMachine &TM,
                                   std::unique_ptr<MCStreamer> Streamer)
    : AsmPrinter(TM, std::move(Streamer)), MCInstLowering(OutContext, *this) {
}

void SPEX64AsmPrinter::emitInstruction(const MachineInstr *MI) {
  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

SPEX64AsmPrinter::~SPEX64AsmPrinter() = default;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSPEX64AsmPrinter() {
  RegisterAsmPrinter<SPEX64AsmPrinter> X(getTheSPEX64Target());
}
