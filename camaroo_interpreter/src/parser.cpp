#include <parser.h>
#include <tokenizer.h>


namespace camaroo_core {

	Parser::Parser(const std::string& source_code)
		:current_token(std::nullopt), tokenizer(Tokenizer(source_code))
	{
		current_token = tokenizer.next_token();
	}

	Program Parser::parse_program() {
		Program program;

		// num32 x = 4;
		while (current_token.has_value()) {
			std::unique_ptr<StatementNode> stmnt = nullptr;
			switch (current_token.value().type)
			{
				case TokenType::unknown:
					break;
				case TokenType::num:
					stmnt = parse_assign_stmnt();
			}
		}

		return program;
	}

	std::unique_ptr<AssignStmnt> Parser::parse_assign_stmnt() {
		Token assign_type = current_token.value();
		current_token = tokenizer.next_token();
		if (!current_token.has_value())
			return nullptr; // TODO: Better error handelling;
		IdentifierNode identifier(current_token.value().value);
	}

}
