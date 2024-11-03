#pragma once

#include <tokenizer.h>
#include <string>
#include <memory>

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
            :toggle_token(token) {}

        virtual TokenType token_type() override { return toggle_token.type; }
        virtual std::string token_value() override { return toggle_token.value; }
        virtual std::string to_string() override { return toggle_token.value; }
    private:
        Token toggle_token; // No nodes
    };

    class Num8Expr : public ExpressionNode {
    public:
        Num8Expr(const Token& token)
            :num_token(token) {}

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
    };

    class Num16Expr : public ExpressionNode {
    public:
        Num16Expr(const Token& token)
            :num_token(token) {}

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
    };

    class Num32Expr : public ExpressionNode {
    public:
        Num32Expr(const Token& token)
            :num_token(token) {}

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token;  // No nodes
    };

    class Num64Expr : public ExpressionNode {
    public:
        Num64Expr(const Token& token)
            :num_token(token) {}

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
    };

    class Fnum64Expr : public ExpressionNode {
    public:
        Fnum64Expr(const Token& token)
            :num_token(token) {}

        virtual TokenType token_type() override { return num_token.type; }
        virtual std::string token_value() override { return num_token.value; }
        virtual std::string to_string() override { return num_token.value; }
    private:
        Token num_token; // No nodes
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
