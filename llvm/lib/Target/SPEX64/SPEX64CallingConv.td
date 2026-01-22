//===-- SPEX64CallingConv.td - Calling Convention ----------------*- tablegen -*-===//

def CC_SPEX64 : CallingConv<[
  CCIfType<[i8, i16, i32], CCPromoteToType<i64>>,
  CCIfType<[i64], CCAssignToReg<[R0, R1, R2, R3]>>,

  CCAssignToStack<8, 8>
]>;

def RetCC_SPEX64 : CallingConv<[
  CCIfType<[i8, i16, i32], CCPromoteToType<i64>>,
  CCIfType<[i64], CCAssignToReg<[R0]>>
]>;
