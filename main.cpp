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
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" <<std::endl;
	std::cout << "The name of the m_line[0] ~ m_line[6]: " << std::endl;
	std::cout << graph.line(0).name << " " << graph.line(1).name << " " << graph.line(2).name << " " << graph.line(3).name << " " << graph.line(4).name << " " << graph.line(5).name << " " << graph.line(6).name << std::endl;
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" <<std::endl;
	std::cout << "Print the number of the gate :" << graph.get_gates().size() << std::endl;
	std::cout << "Print the gate type of the gates:" << std::endl;
	std::cout << graph.gate(0).get_type() << std::endl;
	std::cout << graph.gate(1).get_type() << std::endl;
	std::cout << graph.gate(2).get_type() << std::endl;
	std::cout << graph.gate(3).get_type() << std::endl;
	std::cout << graph.gate(4).get_type() << std::endl;
	std::cout << graph.gate(5).get_type() << std::endl;
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" <<std::endl;
	std::cout << "The source of the line(6) is ： " << std::endl;
	std::cout << graph.line(6).source << std::endl;
	std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++" <<std::endl;
	std::cout << "The index of the input line with the Nand gate is ： " << std::endl;
	std::vector<line_idx> v_Nand_idx = graph.gate(0).inputs();
	for(auto v : v_Nand_idx)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
	std::cout << "The index of the input line with the Nor gate is ： " << std::endl;
	std::vector<line_idx> v_Nor_idx = graph.gate(1).inputs();
	for(auto v : v_Nor_idx)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;

	std::cout << "The index of the destination of G3gat is ： " << std::endl;
	std::set<gate_idx> line_to_desination = graph.line(2).destination_gates;//输入线的destination的index
	for(auto s : line_to_desination)
	{
		std::cout << s << " ";
	}
	std::cout << std::endl;
	std::cout << " The total number of wires in the circuit is : " << std::endl;
	std::cout << graph.total_line_number() << std::endl;

	return 0;
}
