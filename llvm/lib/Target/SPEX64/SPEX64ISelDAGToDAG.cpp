#include "SPEX64ISelDAGToDAG.h"
#include "SPEX64Subtarget.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/IR/Function.h"

using namespace llvm;

SPEX64DAGToDAGISel::SPEX64DAGToDAGISel(SPEX64TargetMachine &TM)
    : SelectionDAGISel(TM) {}

void SPEX64DAGToDAGISel::Select(SDNode *N) {
  // 기본: TableGen 패턴 매칭에 맡기고, 못하면 SelectCode로
  if (N->isMachineOpcode()) {
    N->setNodeId(-1);
    return;
  }
  SelectCode(N);
}

FunctionPass *llvm::createSPEX64ISelDag(SPEX64TargetMachine &TM) {
  return new SPEX64DAGToDAGISel(TM);
}
