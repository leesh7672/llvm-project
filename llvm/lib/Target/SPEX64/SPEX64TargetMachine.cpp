//===-- SPEX64TargetMachine.cpp -------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "SPEX64TargetMachine.h"
#include "TargetInfo/SPEX64TargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern "C" void LLVMInitializeSPEX64TargetMC();
extern "C" void LLVMInitializeSPEX64AsmPrinter();

extern "C" void LLVMInitializeSPEX64Target() {
  LLVMInitializeSPEX64TargetMC();
  LLVMInitializeSPEX64AsmPrinter();
  RegisterTargetMachine<SPEX64TargetMachine> X(getTheSPEX64Target());
}
