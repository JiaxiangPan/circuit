#include "include/iscas89_parser.h"
#include "include/Time.h"
#include <string>
#include <fstream>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		log_error() << "no input file specified";
		return 1;
	}
	std::ifstream ifs(argv[1]);
	if (!ifs.good())
	{
		log_error() << "can't open file" << argv[1];
		return 1;
	}
	auto Parser = 0;
	auto Solver = 0;
	ElapsedTimer t(true);
	CircuitGraph graph;
	Iscas89Parser parser;
	if (!parser.parse(ifs, graph))
	{
		log_error() << "can't parse file" << argv[1];
		return 1;
	}
	Parser =  t.get_elapsed_us();
	std::cout << "the time of parser:   " << 1.0 * Parser/1000 << "  ms" << std :: endl;

	std::cout << "print the inputs:" << std::endl;
	std::vector<line_idx> v_inputs = graph.inputs();
	for(auto v : v_inputs)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
	std::cout << "print the outputs:" << std::endl;
	std::vector<line_idx> v_outputs = graph.outputs();
	for(auto v : v_outputs)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	std::cout << "print the number of the gate :" << std::endl;
	std::cout << graph.get_gates().size() << std::endl;

	std::cout << "print the gate type of the gates:" << std::endl;
	std::cout << graph.gate(0).get_type() << std::endl;
	std::cout << graph.gate(1).get_type() << std::endl;
	std::cout << graph.gate(2).get_type() << std::endl;
	std::cout << graph.gate(3).get_type() << std::endl;
	std::cout << graph.gate(4).get_type() << std::endl;
	std::cout << graph.gate(5).get_type() << std::endl;
	return 0;
}
