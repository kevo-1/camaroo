#include "parser.h"
#include "evaluator.h"

#include <iostream>

namespace camaroo_core {

    void evaluator::evaluate_program(const Program& program) {
        for(const auto& statement : program.statements) {
            // TODO: Should be moved into evaluate_statement
            if (statement->token_type() == TokenType::num64_type) {
                // Check if identifier already exists
                // If not, then get the identifier and store it somewhere
                ASTNode* id = statement->get_left();
                std::string variable_name = std::get<std::string>(id->token_value());
                camaroo_object* variable_value = evaluate_expression(statement->get_right());
                declared_variables.insert({variable_name, variable_value});
            }
        }
    }

    camaroo_object* evaluator::evaluate_expression(ASTNode* statement) {
        if (!statement) {
            return nullptr;
        }

        if (statement->token_type() == TokenType::num) {
            camaroo_object* new_object = new camaroo_object;
            new_object->variable_type = TokenType::num64_type;
            new_object->variable_value = std::get<int64_t>(statement->token_value());
            return new_object;
        }

        if (statement->token_type() == TokenType::add) {
            camaroo_object* left = evaluate_expression(statement->get_left());
            camaroo_object* right = evaluate_expression(statement->get_right());
            int64_t value = std::get<int64_t>(left->variable_value) + std::get<int64_t>(right->variable_value);
            delete left;
            delete right;

            camaroo_object* new_object = new camaroo_object;
            new_object->variable_type = TokenType::num64_type;
            new_object->variable_value = value;
            return new_object;
        }
    }
}