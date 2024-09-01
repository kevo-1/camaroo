#include <iostream>
#include <fstream>
#include <iterator>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Missing File: camaroo-interpreter needs a file to interpret\n";
		return -1;
	}

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
