#include "SPEX64ISelLowering.h"
#include "SPEX64InstrInfo.h"

private:
SPEX64InstrInfo InstrInfo;
SPEX64FrameLowering FrameLowering;

public:
const SPEX64InstrInfo *getInstrInfo() const override { return &InstrInfo; }
const SPEX64RegisterInfo *getRegisterInfo() const override {
  return &InstrInfo.getRegisterInfo();
}
const SPEX64FrameLowering *getFrameLowering() const override {
  return &FrameLowering;
}
