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
	private:
		Token next_token();
		std::unique_ptr<AssignStmnt> parse_assign_stmnt();
		std::unique_ptr<AssignStmnt> parse_expression();
	private:
		std::optional<Token> current_token;
		Tokenizer tokenizer;
	};

}
