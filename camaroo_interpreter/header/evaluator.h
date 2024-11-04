#include "parser.h"
namespace camaroo_core{
    class evaluator
    {
        public:
        void evaluate_program(const Program& program);
        void evaluate_statement(std::unique_ptr<StatementNode> statement);
    };
}