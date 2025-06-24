#pragma once

#include <stdexcept>
#include <tokenizer.h>
#include <string>
#include <memory>
#include <exception>
#include <variant>

namespace camaroo_core {

    using ASTValue = std::variant<int8_t, int16_t, int32_t, int64_t, bool, float, std::string>;

    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual TokenType token_type() = 0;
        virtual ASTValue token_value() = 0;
        virtual std::string to_string() = 0;

        virtual std::string get_node_type() = 0;
        virtual ASTNode* get_left() { return nullptr; }
        virtual ASTNode* get_right() { return nullptr; }
    };

    class StatementNode : public ASTNode {
        virtual std::string get_node_type() override { return "Statement Node"; };
    };

    class ExpressionNode : public ASTNode {
        virtual std::string get_node_type() override { return "Expression Node"; };
    };

    enum class ExprOrder {
        unknown = 0,
        lowest,
        equals,
        less_greater,
        sum_diff,
        product_div,
        prefix,         // -X or !X
        call,           // myFunction(X)
    };

    class IdentifierNode : public ExpressionNode {
    public:
        IdentifierNode(const Token& token)
            :identifier(token) {}

        virtual TokenType token_type() override { return identifier.type; }
        virtual ASTValue token_value() override { return identifier.value; }

        virtual std::string to_string() override { return "ID: " + identifier.value; }
    private:
        Token identifier; // no nodes
    };

    class PrefixExpr : public ExpressionNode {
    public:
        PrefixExpr(const Token& prefix_token, std::unique_ptr<ExpressionNode> right)
            :token(prefix_token), expr(std::move(right)) {}

        virtual TokenType token_type() override { return token.type; }
        virtual ASTValue token_value() override { return token.value; }
        virtual std::string to_string() override { return token.value + " " + expr->to_string(); }

        virtual ASTNode* get_right() override { return expr.get(); }
    private:
        Token token;
        std::unique_ptr<ExpressionNode> expr;
    };

    class InfixExpr : public ExpressionNode {
    public:
        InfixExpr(const Token& prefix_token, std::unique_ptr<ExpressionNode> left, 
                                                std::unique_ptr<ExpressionNode> right)
            :token(prefix_token), left_expr(std::move(left)), right_expr(std::move(right)) {}

        virtual TokenType token_type() override { return token.type; }
        virtual ASTValue token_value() override { return token.value; }
        virtual std::string to_string() override {
            return "(" + left_expr->to_string() + " " + token.value + " " + right_expr->to_string() + ")";
        }

        virtual ASTNode* get_left() override { return left_expr.get();}
        virtual ASTNode* get_right() override { return right_expr.get(); }
    private:
        Token token;
        std::unique_ptr<ExpressionNode> left_expr;
        std::unique_ptr<ExpressionNode> right_expr;
    };

    class ToggleExpr : public ExpressionNode {
    public:
        ToggleExpr(const Token& token)
            :toggle_token(token)
        {
            if (token.value == "true") {
                literal_value = true;
            } else if (token.value == "false") {
                literal_value = false;
            } else {
                throw std::runtime_error("Couldn't parse toggle type");
            }
        }

        virtual TokenType token_type() override { return toggle_token.type; }
        virtual ASTValue token_value() override { return toggle_token.value; }
        virtual std::string to_string() override { return toggle_token.value; }
        bool get_literal() { return literal_value; }
    private:
        Token toggle_token; // No nodes
        bool literal_value;
    };

    class NumExpr : public ExpressionNode {
    public:
        NumExpr(const Token& token)
            :num_token(token)
        {
            size_t val = std::stoll(token.value);
            if (!(static_cast<int64_t>(val) < INT64_MAX && static_cast<int64_t>(val) > INT64_MIN))
                throw std::runtime_error("Couldn't parse integer literal");
            literal_value = static_cast<int64_t>(val);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual ASTValue token_value() override { return literal_value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
        int64_t literal_value;
    };

    class FNumExpr : public ExpressionNode {
    public:
        FNumExpr(const Token& token)
            :num_token(token)
        {
            float val = std::stof(token.value);
            if (!(static_cast<float>(val) < INT64_MAX && static_cast<float>(val) > INT64_MIN))
                throw std::runtime_error("Couldn't parse integer literal");
            literal_value = static_cast<float>(val);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual ASTValue token_value() override { return literal_value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
        float literal_value;
    };

    class AssignStmnt : public StatementNode {
    public:
        AssignStmnt(const Token& type, std::unique_ptr<IdentifierNode> left, std::unique_ptr<ExpressionNode> right)
            :assignType(type), identifier(std::move(left)), expression(std::move(right)) {}

        virtual TokenType token_type() override { return assignType.type; }
        virtual ASTValue token_value() override { return assignType.value; }
        virtual std::string to_string() override { return assignType.value + " " + identifier->to_string() + " = " + expression->to_string(); }

        virtual ASTNode* get_left() override { return identifier.get(); }
        virtual ASTNode* get_right() override { return expression.get(); }
    private:
        Token assignType; // num64, num32, num16, num8, float64, float32, toggle, letter, text, func
        std::unique_ptr<IdentifierNode> identifier; // left node
        std::unique_ptr<ExpressionNode> expression; // right node
    };

    class PrintStmnt : public StatementNode {
    public:
        PrintStmnt(std::unique_ptr<ExpressionNode> printable)
            :expr(std::move(printable)) {}

        virtual TokenType token_type() override { return TokenType::print; }
        virtual ASTValue token_value() override { return "print"; }
        virtual std::string to_string() override { return "Print: " + expr->to_string(); }

        virtual ASTNode* get_right() override { return expr.get(); }
    private:
        std::unique_ptr<ExpressionNode> expr;
    };
}
