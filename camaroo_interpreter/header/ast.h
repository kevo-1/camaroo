#pragma once

#include <stdexcept>
#include <tokenizer.h>
#include <string>
#include <memory>
#include <exception>

namespace camaroo_core {

    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual TokenType token_type() = 0;
        virtual std::string token_value() = 0;
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
        virtual std::string token_value() override { return token.value; }
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
        virtual std::string token_value() override { return toggle_token.value; }
        virtual std::string to_string() override { return toggle_token.value; }
        bool get_literal() { return literal_value; }
    private:
        Token toggle_token; // No nodes
        bool literal_value;
    };

    class Num8Expr : public ExpressionNode {
    public:
        Num8Expr(const Token& token)
            :num_token(token)
        {
            size_t val = std::stoll(token.value);
            if (!(static_cast<int8_t>(val) < INT8_MAX && static_cast<int8_t>(val) > INT8_MIN))
                throw std::runtime_error("Couldn't parse integer literal");
            literal_value = static_cast<int8_t>(val);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
        int8_t get_literal() { return literal_value; }
    private:
        Token num_token; // No nodes
        int8_t literal_value;
    };

    class Num16Expr : public ExpressionNode {
    public:
        Num16Expr(const Token& token)
            :num_token(token)
        {

            size_t val = std::stoll(token.value);
            if (!(static_cast<int16_t>(val) < INT16_MAX && static_cast<int16_t>(val) > INT16_MIN))
                throw std::runtime_error("Couldn't parse integer literal");
            literal_value = static_cast<int16_t>(val);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
        int16_t get_literal() { return literal_value; }
    private:
        Token num_token; // No nodes
        int16_t literal_value;
    };

    class Num32Expr : public ExpressionNode {
    public:
        Num32Expr(const Token& token)
            :num_token(token)
        {
            size_t val = std::stoll(token.value);
            if (!(static_cast<int32_t>(val) < INT32_MAX && static_cast<int32_t>(val) > INT32_MIN))
                throw std::runtime_error("Couldn't parse integer literal");
            literal_value = static_cast<int32_t>(val);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
        int32_t get_literal() { return literal_value; }
    private:
        Token num_token;  // No nodes
        int32_t literal_value;
    };

    class Num64Expr : public ExpressionNode {
    public:
        Num64Expr(const Token& token)
            :num_token(token)
        {
            size_t val = std::stoll(token.value);
            if (!(static_cast<int64_t>(val) < INT64_MAX && static_cast<int64_t>(val) > INT64_MIN))
                throw std::runtime_error("Couldn't parse integer literal");
            literal_value = static_cast<int64_t>(val);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
        int64_t get_literal() { return literal_value; }
    private:
        Token num_token; // No nodes
        int64_t literal_value;
    };

    class Fnum64Expr : public ExpressionNode {
    public:
        Fnum64Expr(const Token& token)
            :num_token(token)
        {
            literal_value = std::stof(token.value);
        }

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
        float get_literal() { return literal_value; }
    private:
        Token num_token; // No nodes
        float literal_value;
    };

    class AssignStmnt : public StatementNode {
    public:
        AssignStmnt(const Token& type, std::unique_ptr<IdentifierNode> left, std::unique_ptr<ExpressionNode> right)
            :assignType(type), identifier(std::move(left)), expression(std::move(right)) {}

        virtual TokenType token_type() override { return assignType.type; }
        virtual std::string token_value() override { return assignType.value; }
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
        virtual std::string token_value() override { return "print"; }
        virtual std::string to_string() override { return "Print: " + expr->to_string(); }

        virtual ASTNode* get_right() override { return expr.get(); }
    private:
        std::unique_ptr<ExpressionNode> expr;
    };
}
