#pragma once

#include <tokenizer.h>
#include <string>

namespace camaroo_core {

	class Node {
	public:
		virtual TokenType token_type() = 0;
		virtual std::string to_string() = 0;
	};

	class StatementNode : public Node {};
	class ExpressionNode : public Node {};

	class IdentifierNode : public ExpressionNode {
	public:
		IdentifierNode(const std::string& value) {
			identifier = { TokenType::identifier, value };
		}
		virtual TokenType token_type() override { return identifier.type; }
		virtual std::string to_string() override { return "ID: " + identifier.value; }
	private:
		Token identifier; // no nodes
	};

	// num32 x = 5;
	// num32 y = 5;
	// x = 5 + y;
	class AssignStmnt : public StatementNode {
	public:
		AssignStmnt(IdentifierNode* left, ExpressionNode* right)
			:identifier(left), expression(right) {}
		virtual TokenType token_type() override { return assignType.type; }
		IdentifierNode* get_identifier() { return identifier; }
		ExpressionNode* get_expression() { return expression; }
		virtual std::string to_string() override { return assignType.value + " " + identifier->to_string() + " = " + expression->to_string(); }
	private:
		Token assignType; // num64, num32, num16, num8, float64, float32, toggle, letter, text, func
		IdentifierNode* identifier; // left node
		ExpressionNode* expression; // right node
	};

	class NumExpr : public ExpressionNode {
	public:
		virtual TokenType token_type() override { return numToken.type; }
		std::string get_value() { return numToken.value; }
		virtual std::string to_string() override { return numToken.value; }
	private:
		Token numToken; // No nodes
	};


}
