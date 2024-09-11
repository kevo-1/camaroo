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

	bool Parser::validate_in_tokens(std::vector<Token>& expected_tokens) {
		if (!current_token.has_value()) {
			found_error(expected_tokens[0].value);
			return false;
		}

		for (const auto& expected_token : expected_tokens) {
			if (current_token.value().type == expected_token.type) {
				return true;
			}
		}

		std::string msg = "Expected next token to be one of [";
		for (const auto token : expected_tokens)
			msg += token.value + " ";
		msg += "] but found, " + current_token.value().value;
		errors.push_back(msg);
		return false;
	}


	bool Parser::validate_token(Token expected_token) {
		if (!current_token.has_value()) {
			found_error(expected_token.value);
			return false;
		}

		if (current_token.value().type != expected_token.type) {
			found_error(expected_token.value);
			return false;
		}

		return true;
	}

	void Parser::found_error(std::string token_type) {
		std::string msg = "Expected next token to be " + token_type +
						" but found, " + (current_token.has_value() ? current_token.value().value : "null");
		errors.push_back(msg);
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
					if (errors.size() > 0)
						return program;
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

		if (!validate_token(Token{TokenType::unknown, "identifier"}))
			return nullptr;
		
		std::unique_ptr<IdentifierNode> id = std::make_unique<IdentifierNode>(current_token.value().value);
		std::unique_ptr<ExpressionNode> value = nullptr;

		// FIX: temporary solution for int only.
		// This is in place for in the case where a variable isn't given
		// a value initially. Example: num32 x; // should be = 0
		current_token = tokenizer.next_token();
		std::vector valid_tokens = {Token({TokenType::semicolon, ";"}), Token({TokenType::equal, "="})};
		if (!validate_in_tokens(valid_tokens))
			return nullptr;

		if (current_token.value().type != TokenType::equal) {
			if (!validate_token(Token{TokenType::semicolon, ";"}))
				return nullptr;
			if (current_token.value().type == TokenType::semicolon) {
				if (assign_type.type == TokenType::num32_type)
					value = std::make_unique<NumExpr>(Token{TokenType::num, "0"});
			}
		}

		if (!value) {
			if (!validate_token(Token({TokenType::num, "number"})))
				return nullptr;
		}

		std::unique_ptr<AssignStmnt> stmnt(new AssignStmnt(assign_type, std::move(id), std::move(value)));
		return stmnt;
	}

}
