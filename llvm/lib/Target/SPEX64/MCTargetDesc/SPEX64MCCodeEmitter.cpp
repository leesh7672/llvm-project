//===-- SPEX64MCCodeEmitter.cpp - SPEX64 MC code emitter --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "SPEX64FixupKinds.h"
#include "SPEX64MCTargetDesc.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdint>

namespace llvm {
namespace {

class SPEX64MCCodeEmitter : public MCCodeEmitter {
  MCContext &Ctx;

  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

public:
  SPEX64MCCodeEmitter(MCContext &Ctx, const MCInstrInfo &) : Ctx(Ctx) {}
  ~SPEX64MCCodeEmitter() override = default;

  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
};

unsigned
SPEX64MCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {
  (void)MI;
  (void)Fixups;
  (void)STI;
  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());
  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());
  if (MO.isExpr())
    return 0;
  return 0;
}

void SPEX64MCCodeEmitter::encodeInstruction(const MCInst &MI,
                                            SmallVectorImpl<char> &CB,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {
  uint32_t W0 = static_cast<uint32_t>(getBinaryCodeForInstr(MI, Fixups, STI));

  // Defensive: If we ever emit a SYS opcode (OPC12==0) with non-zero K9,
  // the encoding is illegal per the ISA spec and usually indicates that a
  // pseudo/unsupported MCInst reached the emitter or an encoding bug exists.
  //
  // This catches the observed 0x000000E0 case (OPC12=0, K9=0x0E0).
  const uint32_t Opc12 = (W0 >> 20) & 0xFFFu;
  const uint32_t K9 = (W0 & 0x1FFu);
  if (Opc12 == 0 && K9 != 0) {
    llvm::errs()
        << "SPEX64MCCodeEmitter: illegal W0 encoding (OPC12=0, K9!=0)\n";
    llvm::errs() << "  W0=0x" << llvm::format_hex(W0, 10) << "\n";
    llvm::errs() << "  MCInst opcode=" << MI.getOpcode()
                 << " operands=" << MI.getNumOperands() << "\n";
    llvm::report_fatal_error(
        "SPEX64MCCodeEmitter produced illegal W0; see dump above.");
  }

  unsigned Size = 4;
  if (W0 & (1u << 16)) {
    Size = (W0 & (1u << 15)) ? 12 : 8;
  }
  const MCExpr *Expr = nullptr;
  for (unsigned I = 0, E = MI.getNumOperands(); I < E; ++I) {
    const MCOperand &Op = MI.getOperand(I);
    if (Op.isExpr()) {
      Expr = Op.getExpr();
      break;
    }
  }

  if (Size <= 4) {
    if (Expr)
      Fixups.push_back(
          MCFixup::create(0, Expr, (MCFixupKind)SPEX64::fixup_spex64_32));
    support::endian::write(CB, W0, endianness::little);
    return;
  }

  const MCOperand *ImmOp = nullptr;
  for (unsigned I = 0, E = MI.getNumOperands(); I < E; ++I) {
    const MCOperand &Op = MI.getOperand(I);
    if (Op.isExpr()) {
      ImmOp = &Op;
      break;
    }
  }
  if (!ImmOp) {
    for (unsigned I = 0, E = MI.getNumOperands(); I < E; ++I) {
      const MCOperand &Op = MI.getOperand(I);
      if (Op.isImm()) {
        ImmOp = &Op;
        break;
      }
    }
  }

  uint32_t Imm32 = 0;
  uint64_t Imm64 = 0;
  if (ImmOp) {
    if (ImmOp->isImm()) {
      Imm64 = static_cast<uint64_t>(ImmOp->getImm());
      Imm32 = static_cast<uint32_t>(Imm64);
    } else if (ImmOp->isExpr()) {
      MCFixupKind Kind = (Size == 8) ? (MCFixupKind)SPEX64::fixup_spex64_32
                                     : (MCFixupKind)SPEX64::fixup_spex64_64;
      Fixups.push_back(MCFixup::create(4, ImmOp->getExpr(), Kind));
    }
  }

  support::endian::write(CB, W0, endianness::little);
  if (Size == 8) {
    support::endian::write(CB, Imm32, endianness::little);
  } else if (Size == 12) {
    support::endian::write(CB, Imm64, endianness::little);
  }
}

} // namespace

MCCodeEmitter *createSPEX64MCCodeEmitter(const MCInstrInfo &MCII,
                                         MCContext &Ctx) {
  return new SPEX64MCCodeEmitter(Ctx, MCII);
}

#include "SPEX64GenMCCodeEmitter.inc"

} // namespace llvm
