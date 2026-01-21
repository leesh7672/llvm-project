//===--- SPEX64.h - Declare SPEX64 target feature support -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_SPEX64_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_SPEX64_H

#include "clang/Basic/TargetInfo.h"
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {

class SPEX64TargetInfo : public TargetInfo {
public:
  SPEX64TargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts);

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  llvm::SmallVector<Builtin::InfosShard> getTargetBuiltins() const override;

  std::string_view getClobbers() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override;

  ArrayRef<const char *> getGCCRegNames() const override;

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override;
};

} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_SPEX64_H
