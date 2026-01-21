#ifndef LLVM_LIB_TARGET_SPEX64_SPEX64ISELDAGTODAG_H
#define LLVM_LIB_TARGET_SPEX64_SPEX64ISELDAGTODAG_H

#include "SPEX64TargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {

class SPEX64DAGToDAGISel : public SelectionDAGISel {
public:
  explicit SPEX64DAGToDAGISel(SPEX64TargetMachine &TM);

  StringRef getPassName() const override {
    return "SPEX64 DAG->DAG Instruction Selector";
  }

  void Select(SDNode *N) override;

#include "SPEX64GenDAGISel.inc"
};

FunctionPass *createSPEX64ISelDag(SPEX64TargetMachine &TM);

} // namespace llvm

#endif
