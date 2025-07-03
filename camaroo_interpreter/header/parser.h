#pragma once

#include <ast.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

namespace camaroo_core {

    struct Program {
        std::vector<std::unique_ptr<StatementNode>> statements;
        bool has_compiled = true;
    };

    class Parser {
    public:
        Parser(const std::string& source_code);
        Program parse_program();
    public:
        std::vector<std::string> errors;
    private:
        std::unique_ptr<AssignStmnt> parse_assign_stmnt();
        std::unique_ptr<PrintStmnt> parse_print_stmnt();
        std::unique_ptr<ExpressionNode> parse_expression(ExprOrder precedent);
        std::unique_ptr<ExpressionNode> parse_grouped_expr();
        std::unique_ptr<ExpressionNode> parse_num_expr();
        std::unique_ptr<ExpressionNode> parse_fnum_expr();
        std::unique_ptr<ExpressionNode> parse_id_expr();
        std::unique_ptr<ExpressionNode> parse_infix_expr(std::unique_ptr<ExpressionNode> left_expr);
        std::unique_ptr<ExpressionNode> parse_toggle_expr();
        std::unique_ptr<ExpressionNode> parse_prefix_expr();
        std::unique_ptr<ExpressionNode> parse_text_expr();
        std::unique_ptr<StatementNode> parse_block_stmnt();
    private:
        void advance_token();
        ExprOrder current_precedence();
        ExprOrder next_precedence();
        bool validate_token(Token expected_token, bool error = true);
        bool validate_in_tokens(std::vector<Token>& expected_tokens);
        void found_error(std::string token_type);
    private:
        std::optional<Token> current_token;
        std::optional<Token> next_token;
        Tokenizer tokenizer;
        std::unordered_map<TokenType, ExprOrder> precedences;
        std::unordered_map<TokenType, std::function<std::unique_ptr<ExpressionNode>()>> prefix_fns;
        std::unordered_map<TokenType, std::function<std::unique_ptr<ExpressionNode>(std::unique_ptr<ExpressionNode>)>> infix_fns;
    };

}
