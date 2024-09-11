#pragma once

#include <ast.h>
#include <vector>
#include <memory>

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
		Token next_token();
		bool validate_token(Token expected_token);
		bool validate_in_tokens(std::vector<Token>& expected_tokens);
		void found_error(std::string token_type);
		std::unique_ptr<AssignStmnt> parse_assign_stmnt();
		std::unique_ptr<AssignStmnt> parse_expression();
	private:
		std::optional<Token> current_token;
		Tokenizer tokenizer;
	};

}
