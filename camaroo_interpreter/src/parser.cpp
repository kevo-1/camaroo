#include <parser.h>
#include <tokenizer.h>
#include <ast.h>
#include <float.h>
#include <memory>
#include <string>

#include <iostream>

namespace camaroo_core {

    Parser::Parser(const std::string& source_code)
        :current_token(std::nullopt), next_token(std::nullopt), tokenizer(Tokenizer(source_code))
    {
        advance_token();
        using expr_ptr = std::unique_ptr<ExpressionNode>;

        // Identifier/Values
        prefix_fns[TokenType::identifier] = [this]() -> expr_ptr { return this->parse_id_expr(); };
        prefix_fns[TokenType::num] = [this]() -> expr_ptr { return this->parse_num_expr(); };
        prefix_fns[TokenType::fnum] = [this]() -> expr_ptr { return this->parse_fnum_expr(); };
        prefix_fns[TokenType::toggle] = [this]() -> expr_ptr { return this->parse_toggle_expr(); };
        prefix_fns[TokenType::LParen] = [this]() -> expr_ptr { return this->parse_grouped_expr(); };
        //Types
        prefix_fns[TokenType::num8_type] = [this]() -> expr_ptr { return this->parse_num_expr(); };
        prefix_fns[TokenType::num16_type] = [this]() -> expr_ptr { return this->parse_num_expr(); };
        prefix_fns[TokenType::num32_type] = [this]() -> expr_ptr { return this->parse_num_expr(); };
        prefix_fns[TokenType::num64_type] = [this]() -> expr_ptr { return this->parse_num_expr(); };
        prefix_fns[TokenType::fnum64_type] = [this]() -> expr_ptr { return this->parse_fnum_expr(); };
        prefix_fns[TokenType::toggle_type] = [this]() -> expr_ptr { return this->parse_toggle_expr(); };
        prefix_fns[TokenType::subtract] = [this]() -> expr_ptr { return this->parse_prefix_expr(); };
        // Operations
        infix_fns[TokenType::add] = [this](expr_ptr expr) -> expr_ptr { return this->parse_infix_expr(std::move(expr)); };
        infix_fns[TokenType::subtract] = [this](expr_ptr expr) -> expr_ptr { return this->parse_infix_expr(std::move(expr)); };
        infix_fns[TokenType::multiply] = [this](expr_ptr expr) -> expr_ptr { return this->parse_infix_expr(std::move(expr)); };
        infix_fns[TokenType::division] = [this](expr_ptr expr) -> expr_ptr { return this->parse_infix_expr(std::move(expr)); };
        infix_fns[TokenType::equal_operator] = [this](expr_ptr expr) -> expr_ptr { return this->parse_infix_expr(std::move(expr)); };

        precedences[TokenType::equal_operator] = ExprOrder::equals;
        precedences[TokenType::add] = ExprOrder::sum_diff;
        precedences[TokenType::subtract] = ExprOrder::sum_diff;
        precedences[TokenType::multiply] = ExprOrder::product_div;
        precedences[TokenType::division] = ExprOrder::product_div;
    }

    bool Parser::validate_in_tokens(std::vector<Token>& expected_tokens) {
        if (!current_token.has_value()) {
            found_error(expected_tokens[0].value);
            return false;
        }

        for (const auto& expected_token : expected_tokens) {
            if (current_token.value().type == expected_token.type) {
                return true;
            }
        }

        std::string msg = "Expected next token to be one of [";
        for (const auto token : expected_tokens)
            msg += token.value + " ";
        msg += "] but found, " + current_token.value().value;
        errors.push_back(msg);
        return false;
    }

    bool Parser::validate_token(Token expected_token) {
        if (!current_token.has_value()) {
            found_error(expected_token.value);
            return false;
        }

        if (current_token.value().type != expected_token.type) {
            found_error(expected_token.value);
            return false;
        }

        return true;
    }

    void Parser::found_error(std::string token_type) {
        std::string msg = "Error: expected next token to be " + token_type +
                        " but found, " + (current_token.has_value() ? current_token.value().value : "null");
        errors.push_back(msg);
    }

    ExprOrder Parser::current_precedence() {
        auto it = precedences.find(current_token.value().type);
        if (it != precedences.end())
            return precedences[current_token.value().type];
        return ExprOrder::lowest;
    }

    ExprOrder Parser::next_precedence() {
        if (!next_token.has_value())
            return ExprOrder::lowest;

        auto it = precedences.find(next_token.value().type);
        if (it != precedences.end())
            return precedences[next_token.value().type];
        return ExprOrder::lowest;
    }

    void Parser::advance_token() {
        current_token = tokenizer.next_token();
        next_token = tokenizer.peek_next_token();
    }

    Program Parser::parse_program() {
        Program program;

        while (current_token.has_value()) {
            std::unique_ptr<StatementNode> stmnt = nullptr;
            switch (current_token.value().type) {
                case TokenType::unknown:
                    errors.push_back("Unknown token: " + current_token.value().value);
                    break;
                case TokenType::num8_type:
                case TokenType::num16_type:
                case TokenType::num32_type:
                case TokenType::num64_type:
                case TokenType::fnum64_type:
                case TokenType::toggle_type:
                    stmnt = parse_assign_stmnt();
                    if (errors.size() > 0)
                        return program;
                    break;
                case TokenType::print:
                    stmnt = parse_print_stmnt();
                    if (errors.size() > 0)
                        return program;
                    break;
                default:
                    break;
            }

            if (stmnt) {
                program.statements.push_back(std::move(stmnt));
            } else {
                errors.push_back("Error: statement is incorrect at " + current_token.value().value);
                return program;
            }
            advance_token();
        }
        return program;
    }
    std::unique_ptr<PrintStmnt> Parser::parse_print_stmnt() {
        advance_token();
        if (!validate_token({TokenType::LParen, "("}))
            return nullptr;

        std::unique_ptr<ExpressionNode> expr = parse_expression(ExprOrder::lowest);
        advance_token();

        if (!validate_token({TokenType::semicolon, ";"}))
            return nullptr;

        return (expr) ? std::make_unique<PrintStmnt>(std::move(expr)) : nullptr;
    }
    std::unique_ptr<AssignStmnt> Parser::parse_assign_stmnt() {
        Token assign_type = current_token.value();
        advance_token();

        if (!validate_token(Token{TokenType::identifier, "identifier"}))
            return nullptr;

        current_token.value().type = TokenType::identifier;
        std::unique_ptr<IdentifierNode> id = std::make_unique<IdentifierNode>(current_token.value());
        std::unique_ptr<ExpressionNode> value = nullptr;
        advance_token();
        std::vector valid_tokens = {Token({TokenType::semicolon, ";"}), Token({TokenType::equal, "="})};
        if (!validate_in_tokens(valid_tokens))
            return nullptr;

        if (current_token.value().type == TokenType::semicolon) {
                value = prefix_fns[assign_type.type]();
        } else {
            advance_token();
            value = parse_expression(ExprOrder::lowest);
            advance_token();
        }

        if (!validate_token({TokenType::semicolon, ";"}))
            return nullptr;

        return (id && value) ? std::make_unique<AssignStmnt>(assign_type, std::move(id), std::move(value)) : nullptr;
    }

    std::unique_ptr<ExpressionNode> Parser::parse_expression(ExprOrder precedence) {
        if (!current_token.has_value()) {
            errors.push_back("Error: expected expression or ; but found none");
            return nullptr;
        }

        auto prefix_it = prefix_fns.find(current_token.value().type);
        if (prefix_it == prefix_fns.end()) {
            errors.push_back("Error: couldn't parse " + current_token.value().value);
            return nullptr;
        }

        Token token_to_parse = current_token.value();
        std::unique_ptr<ExpressionNode> left = prefix_fns[token_to_parse.type]();
        if (!left) {
            errors.push_back("Error: coudln't parse expression at " + token_to_parse.value);
            return nullptr;
        }

        while (next_token.has_value()) {
            if (next_token.value().type == TokenType::semicolon || next_precedence() <= precedence)
                break;

            advance_token();
            if (!current_token.has_value()) {
                errors.push_back("Error: expected expression or ; but found none");
                return nullptr;
            }

            auto infix_it = infix_fns.find(current_token.value().type);
            if (infix_it == infix_fns.end()) {
                errors.push_back("Error: couldn't parse " + current_token.value().value);
                return nullptr;
            }

            if (!current_token.has_value()) {
                errors.push_back("Error: expected expression or ; but found none");
                return nullptr;
            }

            token_to_parse = current_token.value();
            left = infix_fns[token_to_parse.type](std::move(left));

            if (!left) {
                errors.push_back("Error: coudln't parse expression at " + token_to_parse.value);
                return nullptr;
            }
        }

        return left;
    }

    std::unique_ptr<ExpressionNode> Parser::parse_prefix_expr() {
        Token token = current_token.value();
        ExprOrder precedence = current_precedence();
        advance_token();
        if (!current_token.has_value())
            return nullptr;
        std::unique_ptr<ExpressionNode> right_expr = parse_expression(precedence);
        return std::unique_ptr<PrefixExpr>(new PrefixExpr(token, std::move(right_expr)));
    }

    std::unique_ptr<ExpressionNode> Parser::parse_infix_expr(std::unique_ptr<ExpressionNode> left_expr) {
        Token infix_type = current_token.value();
        ExprOrder precedence = current_precedence();
        advance_token();
        if (!current_token.has_value())
            return nullptr;

        std::unique_ptr<ExpressionNode> right_expr = parse_expression(precedence);
        return std::unique_ptr<ExpressionNode>(new InfixExpr(infix_type, std::move(left_expr), std::move(right_expr)));
    }

    std::unique_ptr<ExpressionNode> Parser::parse_grouped_expr() {
        advance_token();
        if (!current_token.has_value())
            return nullptr;

        std::unique_ptr<ExpressionNode> expr = parse_expression(ExprOrder::lowest);
        advance_token();

        if (!validate_token({TokenType::RParen, ")"}))
            return nullptr;

        return expr;
    }

    std::unique_ptr<ExpressionNode> Parser::parse_id_expr() {
        return std::unique_ptr<IdentifierNode>(new IdentifierNode(current_token.value()));
    }

    std::unique_ptr<ExpressionNode> Parser::parse_toggle_expr() {
        return std::unique_ptr<ToggleExpr>(new ToggleExpr(current_token.value()));
    }

    std::unique_ptr<ExpressionNode> Parser::parse_num_expr() {
        if (current_token.value().type == TokenType::semicolon)
            return std::unique_ptr<Num32Expr>(new Num32Expr(Token({TokenType::num, "0"})));

        size_t val = std::stoll(current_token.value().value);
        if (static_cast<int8_t>(val) < INT8_MAX && static_cast<int8_t>(val) > INT8_MIN)
            return std::unique_ptr<Num8Expr>(new Num8Expr(current_token.value()));
        else if (static_cast<int16_t>(val) < INT16_MAX && static_cast<int16_t>(val) > INT16_MIN)
            return std::unique_ptr<Num16Expr>(new Num16Expr(current_token.value()));
        else if (static_cast<int32_t>(val) < INT32_MAX && static_cast<int32_t>(val) > INT32_MIN)
            return std::unique_ptr<Num32Expr>(new Num32Expr(current_token.value()));
        else if (static_cast<int64_t>(val) < INT64_MAX && static_cast<int64_t>(val) > INT64_MIN)
            return std::unique_ptr<Num64Expr>(new Num64Expr(current_token.value()));

        errors.push_back("Error: couldn't convert number literal to correct size");
        return nullptr;
    }

    std::unique_ptr<ExpressionNode> Parser::parse_fnum_expr() {
        if (current_token.value().type == TokenType::semicolon)
            return std::unique_ptr<Fnum64Expr>(new Fnum64Expr(Token({TokenType::fnum, "0"})));

        size_t val = std::stod(current_token.value().value);
        if (static_cast<double>(val) < DBL_MAX && static_cast<double>(val) > DBL_MIN)
            return std::unique_ptr<Fnum64Expr>(new Fnum64Expr(current_token.value()));

        errors.push_back("Error: couldn't convert float literal to correct size");
        return nullptr;
    }

}
