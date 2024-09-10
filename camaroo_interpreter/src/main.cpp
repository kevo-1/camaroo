#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "tokenizer.h"

const std::string version = "0.0.1";

void CLI_interface() {
    std::cout << "Welcome to Camaroo " << version << std::endl;
    std::cout << ">>> ";
}

void process_line(const std::string& text) {
   camaroo_core::Tokenizer temp_tokenizer(text);
   std::optional<camaroo_core::Token> token = temp_tokenizer.next_token();
   while (token.has_value()) {
        std::cout << '(' << token.value().value << ")\n";
        token = temp_tokenizer.next_token();
   }
}



int main(int argc, char** argv) {
    if (argc == 2) {
        std::ifstream source_file(argv[1]);
        std::string source_code;

        source_file.seekg(0, std::ios::end);
        source_code.reserve(source_file.tellg());
        source_file.seekg(0, std::ios::beg);

        source_code.assign(std::istreambuf_iterator<char>(source_file),
                    std::istreambuf_iterator<char>());

        std::cout << source_code << std::endl;
        return 0;
    }
    

    CLI_interface();
    while (true) {
        std::string line; 
        std::getline(std::cin, line);
        if (line == "exit") break;
        process_line(line);
        std::cout << ">>> ";
    }

}
