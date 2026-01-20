include "SPEX64RegisterInfo.td"

class SPEX64Instr<string asmstr, dag outs, dag ins> : Instruction {
  let Namespace = "SPEX64";
  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString      = asmstr;
}

def SPEX64InstrInfo : InstrInfo;

def NOP : SPEX64Instr<"nop", (outs), (ins)>;

defm : RemapAllTargetPseudoPointerOperands<GPR>;

