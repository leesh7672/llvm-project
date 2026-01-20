#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class SPEX64AsmBackend : public MCAsmBackend {
public:
  SPEX64AsmBackend() : MCAsmBackend(support::little) {}

  std::unique_ptr<MCObjectTargetWriter>
  createObjectTargetWriter() const override {
    llvm_unreachable("Use createSPEX64ELFObjectWriter()");
  }

  std::unique_ptr<MCObjectWriter>
  createObjectWriter(raw_pwrite_stream &OS) const override {
    llvm_unreachable("Registered via RegisterMCObjectWriter()");
  }

  void applyFixup(const MCAssembler &, const MCFixup &, const MCValue &,
                  MutableArrayRef<char>, uint64_t, bool) const override {
  }

  bool mayNeedRelaxation(const MCInst &) const override { return false; }
  void relaxInstruction(const MCInst &, const MCSubtargetInfo &, MCInst &) const override {
    llvm_unreachable("relaxation not implemented");
  }

  bool writeNopData(raw_ostream &OS, uint64_t Count,
                    const MCSubtargetInfo *) const override {
    const uint32_t W0 = 0;
    while (Count >= 4) {
      OS.write(reinterpret_cast<const char *>(&W0), 4);
      Count -= 4;
    }
    return Count == 0;
  }

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override {
    static const MCFixupKindInfo Infos[] = {
        {"FK_NONE", 0, 0, 0},
    };
    if (Kind >= FirstTargetFixupKind)
      return Infos[0];
    return MCAsmBackend::getFixupKindInfo(Kind);
  }
};
} // namespace

MCAsmBackend *createSPEX64AsmBackend(const Target &, const MCSubtargetInfo &,
                                     const MCRegisterInfo &,
                                     const MCTargetOptions &) {
  return new SPEX64AsmBackend();
}
