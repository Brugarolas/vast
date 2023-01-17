// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include "vast/Util/Warnings.hpp"

VAST_RELAX_WARNINGS
#include <clang/Frontend/FrontendAction.h>
VAST_UNRELAX_WARNINGS

#include "vast/Util/Common.hpp"
#include "vast/Frontend/CompilerInstance.hpp"
#include "vast/Frontend/FrontendAction.hpp"
#include "vast/CodeGen/Generator.hpp"

namespace llvm {
    class LLVMIRContext;
    class Module;
} // namespace llvm

namespace mlir {
    class MLIRContext;
    class ModuleOp;
} // namespace mlir

namespace vast::cc {

    namespace opt {
        constexpr string_ref emit_high_level = "emit-high-level";
        constexpr string_ref emit_cir = "emit-cir";
    } // namespace opt

    struct vast_gen_consumer;

    struct vast_gen_action : frontend_action {
        virtual ~vast_gen_action() = default;

        vast_gen_consumer *consumer;
        output_type action;

    protected:

        vast_gen_action(output_type action, mcontext_t *mcontext = nullptr);

        std::unique_ptr< clang::ASTConsumer >
        CreateASTConsumer(compiler_instance &ci, llvm::StringRef InFile) override;

        void ExecuteAction() override;

        void EndSourceFileAction() override;

    private:
        friend struct vast_gen_consumer;

        OwningModuleRef mlir_module;
        // std::unique_ptr< llvm::Module > llvm_module;

        mcontext_t *mcontext;

        OwningModuleRef load_module(llvm::MemoryBufferRef mref);
    };

    //
    // Emit assembly
    //
    struct emit_assembly_action : vast_gen_action {
        emit_assembly_action(mcontext_t *mcontext = nullptr);
    private:
        virtual void anchor();
    };

    //
    // Emit LLVM
    //
    struct emit_llvm_action : vast_gen_action {
        emit_llvm_action(mcontext_t *mcontext = nullptr);
    private:
        virtual void anchor();
    };

    //
    // Emit obj
    //
    struct emit_obj_action : vast_gen_action {
        emit_obj_action(mcontext_t *mcontext = nullptr);
    private:
        virtual void anchor();
    };

    //
    // Emit high level mlir dialect
    //
    struct emit_high_level_action : vast_gen_action {
        emit_high_level_action(mcontext_t *mcontext = nullptr);
    private:
        virtual void anchor();
    };

    //
    // Emit cir mlir dialect
    //
    struct emit_cir_action : vast_gen_action {
        emit_cir_action(mcontext_t *mcontext = nullptr);
    private:
        virtual void anchor();
    };

} // namespace vast