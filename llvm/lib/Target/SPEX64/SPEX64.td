include "SPEX64InstInfo.td"
include "SPEX64CallingConv.td"

def SPEX64 : Target {
  let InstructionSet = SPEX64InstrInfo;
}
