#include <memory>
#include <parser.h>
#include <tokenizer.h>
#include <iostream>


namespace camaroo_core {

	Parser::Parser(const std::string& source_code)
		:current_token(std::nullopt), tokenizer(Tokenizer(source_code))
	{
		current_token = tokenizer.next_token();
	}

	Program Parser::parse_program() {
		Program program;

		while (current_token.has_value()) {
			std::unique_ptr<StatementNode> stmnt = nullptr;
			switch (current_token.value().type) {
				case TokenType::unknown:
					// TODO: Check if it's an identifier, if yes, 
					break;
				case TokenType::num32_type:
					stmnt = parse_assign_stmnt();
				default:
					break;
			}

			if (stmnt) {
				program.statements.push_back(std::move(stmnt));
			}
			current_token = tokenizer.next_token();
		}
		return program;
	}

	// num32 x;
	// num32 x = 6;
	// float32 y = 2.4;
	std::unique_ptr<AssignStmnt> Parser::parse_assign_stmnt() {
		Token assign_type = current_token.value();
		current_token = tokenizer.next_token();
		if (!current_token.has_value()) {
			std::cout << "Syntax Error: Couldn't find the rest of the statement\n";
			return nullptr; // TODO: Better error handelling;
		}
		
		std::unique_ptr<IdentifierNode> id = std::make_unique<IdentifierNode>(current_token.value().value);
		std::unique_ptr<ExpressionNode> value = nullptr;

		// FIX: temporary solution for int only.
		// This is in place for in the case where a variable isn't given
		// a value initially. Example: num32 x; // should be = 0
		current_token = tokenizer.next_token();
		if (!current_token.has_value()) {
			std::cout << "Syntax Error: Couldn't find the rest of the statement\n";
			return nullptr; // TODO: Better error handelling;
		}
		if (current_token.value().type != TokenType::equal) {
			if (!current_token.has_value()) {
				std::cout << "Syntax Error: Couldn't find the rest of the statement\n";
				return nullptr; // TODO: Better error handelling;
			}
			if (current_token.value().type == TokenType::semicolon) {
				if (assign_type.type == TokenType::num32_type)
					value = std::make_unique<NumExpr>(Token{TokenType::num, "0"});
			}
		}

		std::unique_ptr<AssignStmnt> stmnt(new AssignStmnt(assign_type, std::move(id), std::move(value)));
		return stmnt;
	}

}
