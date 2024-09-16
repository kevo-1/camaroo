#pragma once

#include <tokenizer.h>
#include <string>
#include <memory>

namespace camaroo_core {

    class Node {
    public:
        virtual TokenType token_type() = 0;
        virtual std::string token_value() = 0;
        virtual std::string to_string() = 0;

        virtual std::string get_node_type() = 0;
        virtual std::weak_ptr<Node> get_left() { return {}; }
        virtual std::weak_ptr<Node> get_right() { return {}; }
    };

    class StatementNode : public Node {
        virtual std::string get_node_type() override { return "Statement Node"; };
    };
    class ExpressionNode : public Node {
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
        virtual std::string token_value() override { return identifier.value; }

        virtual std::string to_string() override { return "ID: " + identifier.value; }
    private:
        Token identifier; // no nodes
    };

    class PrefixExpr : public ExpressionNode {
    public:
        PrefixExpr(const Token& prefix_token, std::unique_ptr<ExpressionNode> right)
            :token(prefix_token), expr(std::move(right)) {}

        virtual TokenType token_type() override { return token.type; }
        virtual std::string token_value() override { return token.value; }
        virtual std::string to_string() override { return token.value + " " + expr->to_string(); }

        virtual std::weak_ptr<Node> get_right() override { return expr; }
    private:
        Token token;
        std::shared_ptr<ExpressionNode> expr;
    };

    class InfixExpr : public ExpressionNode {
    public:
        InfixExpr(const Token& prefix_token, std::unique_ptr<ExpressionNode> left, 
                                                std::unique_ptr<ExpressionNode> right)
            :token(prefix_token), left_expr(std::move(left)), right_expr(std::move(right)) {}

        virtual TokenType token_type() override { return token.type; }
        virtual std::string token_value() override { return token.value; }
        virtual std::string to_string() override {
            return "(" + left_expr->to_string() + " " + token.value + " " + right_expr->to_string() + ")";
        }

        virtual std::weak_ptr<Node> get_left() override { return left_expr;}
        virtual std::weak_ptr<Node> get_right() override { return right_expr; }
    private:
        Token token;
        std::shared_ptr<ExpressionNode> left_expr;
        std::shared_ptr<ExpressionNode> right_expr;
    };

    class ToggleExpr : public ExpressionNode {
    public:
        ToggleExpr(const Token& token)
            :toggle_token(token) {}

        virtual TokenType token_type() override { return toggle_token.type; }
        virtual std::string token_value() override { return toggle_token.value; }
        virtual std::string to_string() override { return toggle_token.value; }
    private:
        Token toggle_token;
    };
    
    class Num8Expr : public ExpressionNode {
    public:
        Num8Expr(const Token& token)
            :num_token(token), value(0)
        {
            int8_t v = static_cast<int8_t>(stoll(token.value));
            if (v > INT8_MAX)
                throw std::range_error("Error: Value is bigger than a num8");
            if (v < INT8_MIN)
                throw std::range_error("Error: Value is smaller than a num8");
            value = stoll(token.value);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
        int8_t value;
    };

    class Num16Expr : public ExpressionNode {
    public:
        Num16Expr(const Token& token)
            :num_token(token), value(0)
        {
            int16_t v = static_cast<int16_t>(stoll(token.value));
            if (v > INT16_MAX)
                throw std::range_error("Error: Value is bigger than a num16");
            if (v < INT16_MIN)
                throw std::range_error("Error: Value is smaller than a num16");
            value = stoll(token.value);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
        int16_t value;
    };

    class Num32Expr : public ExpressionNode {
    public:
        Num32Expr(const Token& token)
            :num_token(token), value(0)
        {
            int32_t v = static_cast<int32_t>(stoll(token.value));
            if (v > INT32_MAX)
                throw std::range_error("Error: Value is bigger than a num32");
            if (v < INT32_MIN)
                throw std::range_error("Error: Value is smaller than a num32");
            value = stoll(token.value);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
        int32_t value;
    };

    class Num64Expr : public ExpressionNode {
    public:
        Num64Expr(const Token& token)
            :num_token(token), value(0)
        {
            int64_t v = stoll(token.value);
            if (v > INT64_MAX)
                throw std::range_error("Error: Value is bigger than a num64");
            if (v < INT64_MIN)
                throw std::range_error("Error: Value is smaller than a num64");
            value = stoll(token.value);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
        int64_t value;
    };

    class AssignStmnt : public StatementNode {
    public:
        AssignStmnt(const Token& type, std::unique_ptr<IdentifierNode> left, std::unique_ptr<ExpressionNode> right)
            :assignType(type), identifier(std::move(left)), expression(std::move(right)) {}

        virtual TokenType token_type() override { return assignType.type; }
        virtual std::string token_value() override { return assignType.value; }
        virtual std::string to_string() override { return assignType.value + " " + identifier->to_string() + " = " + expression->to_string(); }

        std::weak_ptr<Node> get_left() override { return identifier; }
        std::weak_ptr<Node> get_right() override { return expression; }
    private:
        Token assignType; // num64, num32, num16, num8, float64, float32, toggle, letter, text, func
        std::shared_ptr<IdentifierNode> identifier; // left node
        std::shared_ptr<ExpressionNode> expression; // right node
    };
}
