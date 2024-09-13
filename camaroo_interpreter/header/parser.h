#pragma once

#include <ast.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

namespace camaroo_core {

	struct Program {
		std::vector<std::unique_ptr<StatementNode>> statements;
	};

	class Parser {
	public:
		Parser(const std::string& source_code);
		Program parse_program();
	public:
		std::vector<std::string> errors;
	private:
		std::unique_ptr<AssignStmnt> parse_assign_stmnt();
		std::unique_ptr<ExpressionNode> parse_expression(ExprOrder precedent);
		std::unique_ptr<ExpressionNode> parse_num_expr();
		std::unique_ptr<ExpressionNode> parse_id_expr();
	private:
		Token next_token();
		bool validate_token(Token expected_token);
		bool validate_in_tokens(std::vector<Token>& expected_tokens);
		void found_error(std::string token_type);
	private:
		std::optional<Token> current_token;
		Tokenizer tokenizer;
		typedef std::unique_ptr<ExpressionNode> expr_ptr;
		std::unordered_map<TokenType, std::function<expr_ptr()>> prefix_fns;
		std::unordered_map<TokenType, std::function<expr_ptr(expr_ptr)>> infix_fns;
	};

}
