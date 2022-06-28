// Copyright (c) 2022-present, Trail of Bits, Inc.

#include "vast/repl/codegen.hpp"
#include "vast/repl/common.hpp"

#include "vast/repl/state.hpp"

#include "vast/Translation/CodeGen.hpp"

#include <fstream>

namespace vast::repl::codegen {

    std::string slurp(std::ifstream& in) {
        std::ostringstream sstr;
        sstr << in.rdbuf();
        return sstr.str();
    }

    std::unique_ptr< clang::ASTUnit > ast_from_source(const std::string &source) {
        return clang::tooling::buildASTFromCode(source);
    }

    std::string get_source(std::filesystem::path source) {
        std::ifstream in(source);
        return slurp(in);
    }

    owning_module_ref emit_module(const std::string &source, MContext *ctx) {
        auto unit = codegen::ast_from_source(source);
        auto &ast = unit->getASTContext();
        vast::hl::high_level_codegen codegen(ctx);
        return codegen.emit_module(ast.getTranslationUnitDecl());
    }

} // namespace vast::repl::codegen