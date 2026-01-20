#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ELF.h"

using namespace llvm;

std::unique_ptr<MCObjectWriter>
createSPEX64ELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI) {
  auto MOTW = std::make_unique<MCELFObjectTargetWriter>(
      /*Is64Bit=*/true, OSABI, ELF::EM_NONE, /*HasRelocationAddend=*/true);

  return createELFObjectWriter(std::move(MOTW), OS,
                               /*IsLittleEndian=*/true);
}
