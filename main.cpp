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

	std::vector<line_idx> v_inputs = graph.inputs();
	std::cout << "The number of the inputs: " << v_inputs.size() << std::endl;
	std::cout << "Print the input_lines indxe:" << std::endl;
	for(auto v : v_inputs)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" <<std::endl;
	std::vector<line_idx> v_outputs = graph.outputs();
	std::cout << "The number of the outputs: " << v_outputs.size() << std::endl;
	std::cout << "Print the output_lines index:" << std::endl;
	for(auto v : v_outputs)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	std::cout << "Print the number of the gate :" << graph.get_gates().size() << std::endl;
	std::cout << "Print the gate type of the gates:" << std::endl;
	std::cout << graph.gate(0).get_type() << std::endl;
	std::cout << graph.gate(1).get_type() << std::endl;
	std::cout << graph.gate(2).get_type() << std::endl;
	std::cout << graph.gate(3).get_type() << std::endl;
	std::cout << graph.gate(4).get_type() << std::endl;
	std::cout << graph.gate(5).get_type() << std::endl;

	std::cout << "The source of the line(6) is ： " << std::endl;
	std::cout << graph.line(6).source << std::endl;

	std::cout << "The index of the input line with the Nand gate is ： " << std::endl;
	std::vector<line_idx> v_in = graph.gate(0).inputs();
	for(auto v : v_in)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	return 0;
}
