#ifndef LLVM_LIB_TARGET_SPEX64_SPEX64REGISTERINFO_H
#define LLVM_LIB_TARGET_SPEX64_SPEX64REGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "SPEX64GenRegisterInfo.inc"

namespace llvm {

class SPEX64RegisterInfo : public SPEX64GenRegisterInfo {
public:
  SPEX64RegisterInfo();

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  Register getFrameRegister(const MachineFunction &MF) const override;

  Register getStackRegister(const MachineFunction &MF) const;

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;
  bool eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS) const override;
};

} // namespace llvm
#endif
