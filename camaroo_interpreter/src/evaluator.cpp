#include "parser.h"
#include "evaluator.h"

#include <iostream>
#include <algorithm>

namespace camaroo_core {

    void evaluator::evaluate_program(const Program& program) {
        std::vector<TokenType> types = {TokenType::num_type, TokenType::text_type};

        for (const auto& statement : program.statements) {
            // TODO: Should be moved into evaluate_statement
            const auto& it = std::find(types.begin(), types.end(), statement->token_type());
            if (it != types.end()) {
                ASTNode* id = statement->get_left();
                std::string variable_name = std::get<std::string>(id->token_value());
                std::shared_ptr<camaroo_object> variable_value = evaluate_expression(statement->get_right());
                declared_variables.insert({variable_name, variable_value});
                continue;
            }

            if (statement->token_type() == TokenType::equal) {
                ASTNode* id = statement->get_left();
                std::string variable_name = std::get<std::string>(id->token_value());
                std::shared_ptr<camaroo_object> variable_value = evaluate_expression(statement->get_right());
                declared_variables[variable_name] = variable_value;
                continue;
            }

            if (statement->token_type() == TokenType::print) {
                std::shared_ptr<camaroo_object> value = evaluate_expression(statement->get_right());
                if (value->variable_type == TokenType::num) {
                    printf("%i", std::get<int64_t>(value->variable_value));
                } else if (value->variable_type == TokenType::text) {
                    std::cout << std::get<std::string>(value->variable_value);
                }
                continue;
            }
        }
    }

    std::shared_ptr<camaroo_object> evaluator::evaluate_expression(ASTNode* statement) {
        if (!statement) {
            return nullptr;
        }

        if (statement->token_type() == TokenType::identifier) {
            try {
                return declared_variables[std::get<std::string>(statement->token_value())];
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        }

        if (statement->token_type() == TokenType::num) {
            std::shared_ptr<camaroo_object> new_object = std::make_shared<camaroo_object>();
            new_object->variable_type = TokenType::num;
            new_object->variable_value = std::get<int64_t>(statement->token_value());
            return new_object;
        }

        if (statement->token_type() == TokenType::text) {
            std::shared_ptr<camaroo_object> new_object = std::make_shared<camaroo_object>();
            new_object->variable_type = TokenType::text;
            new_object->variable_value = std::get<std::string>(statement->token_value());
            return new_object;
        }

        if (statement->token_type() == TokenType::add) {
            std::shared_ptr<camaroo_object> left = evaluate_expression(statement->get_left());
            std::shared_ptr<camaroo_object> right = evaluate_expression(statement->get_right());
            int64_t value;
            try {
                value = std::get<int64_t>(left->variable_value) + std::get<int64_t>(right->variable_value);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            std::shared_ptr<camaroo_object> new_object = std::make_shared<camaroo_object>();
            new_object->variable_type = TokenType::num;
            new_object->variable_value = value;
            return new_object;
        }

        if (statement->token_type() == TokenType::subtract) {
            std::shared_ptr<camaroo_object> left = evaluate_expression(statement->get_left());
            std::shared_ptr<camaroo_object> right = evaluate_expression(statement->get_right());
            int64_t value;
            try {
                value = std::get<int64_t>(left->variable_value) - std::get<int64_t>(right->variable_value);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            std::shared_ptr<camaroo_object> new_object = std::make_shared<camaroo_object>();
            new_object->variable_type = TokenType::num;
            new_object->variable_value = value;
            return new_object;
        }

        if (statement->token_type() == TokenType::multiply) {
            std::shared_ptr<camaroo_object> left = evaluate_expression(statement->get_left());
            std::shared_ptr<camaroo_object> right = evaluate_expression(statement->get_right());
            int64_t value;
            try {
                value = std::get<int64_t>(left->variable_value) * std::get<int64_t>(right->variable_value);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            std::shared_ptr<camaroo_object> new_object = std::make_shared<camaroo_object>();
            new_object->variable_type = TokenType::num;
            new_object->variable_value = value;
            return new_object;
        }

        if (statement->token_type() == TokenType::division) {
            std::shared_ptr<camaroo_object> left = evaluate_expression(statement->get_left());
            std::shared_ptr<camaroo_object> right = evaluate_expression(statement->get_right());
            int64_t value;
            try {
                value = std::get<int64_t>(left->variable_value) / std::get<int64_t>(right->variable_value);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            std::shared_ptr<camaroo_object> new_object = std::make_shared<camaroo_object>();
            new_object->variable_type = TokenType::num;
            new_object->variable_value = value;
            return new_object;
        }
        return nullptr;
    }
}