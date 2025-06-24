#pragma once

#include "parser.h"
#include <unordered_map>
#include <variant>

namespace camaroo_core {

    using Value = std::variant<int64_t, std::string>;

    struct camaroo_object {
        TokenType variable_type;
        Value variable_value;
    };

    class evaluator {
    public:
        void evaluate_program(const Program& program);
        void evaluate_statement(ASTNode* statement);

        std::shared_ptr<camaroo_object> evaluate_expression(ASTNode* statement);
        camaroo_object* get_variable(const std::string& var_name) { return declared_variables[var_name].get(); }
        const std::unordered_map<std::string, std::shared_ptr<camaroo_object>>& get_variables() { return declared_variables; }

    private:
        std::unordered_map<std::string, std::shared_ptr<camaroo_object>> declared_variables;
    };
}