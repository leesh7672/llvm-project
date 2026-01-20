#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/raw_ostream.h"

#include "SPEX64GenInstrInfo.inc" // NOP enum 필요할 때 대비(없어도 됨)

using namespace llvm;

namespace {
class SPEX64MCCodeEmitter : public MCCodeEmitter {
  const MCInstrInfo &MCII;

public:
  explicit SPEX64MCCodeEmitter(const MCInstrInfo &MCII) : MCII(MCII) {}
  ~SPEX64MCCodeEmitter() override = default;

  void encodeInstruction(const MCInst &Inst, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override {
    (void)Fixups;
    (void)STI;
    uint32_t W0 = 0;

    OS.write(reinterpret_cast<const char *>(&W0), sizeof(W0));
  }
};
} // namespace

MCCodeEmitter *createSPEX64MCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx) {
  (void)Ctx;
  return new SPEX64MCCodeEmitter(MCII);
}
