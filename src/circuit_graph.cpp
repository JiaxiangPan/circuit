#include "../include/circuit_graph.h"
#include "../include/log.h"
#include <iostream>
#include <sstream>
#include <map>
#include <set>

const char *make_gate_name(Gate::Type type)
{
	int flag = -1;
	switch (type)
	{
	case Gate::Type::And:
		return "AND";
		break;
	case Gate::Type::Nand:
		return "NAND";
		break;
	case Gate::Type::Not:
		return "NOT";
		break;
	case Gate::Type::Or:
		return "OR";
		break;
	case Gate::Type::Nor:
		return "NOR";
		break;
	case Gate::Type::Xor:
		return "XOR";
		break;
	case Gate::Type::Xnor:
		return "XNOR";
		break;
	case Gate::Type::Buff:
		return "BUFF";
		break;
	case Gate::Type::Undefined:
		return "UNDEFINED";
		break;
	}
	assert(false);
	return "???";
}

//构造普通门
Gate::Gate(Gate::Type type, line_idx output, std::vector<line_idx> &&inputs) : m_type(type), m_inputs(inputs), m_output(output){}

line_idx CircuitGraph::add_input(const std::string& name)
{
	line_idx p_line = ensure_line(name);
	//m_inputs.push_back(p_line);//bug?
	if (!m_lines[p_line].is_input) 
	{
		m_lines[p_line].is_input = true;
		m_inputs.push_back(p_line);
	}
	return p_line;
}

line_idx CircuitGraph::add_output(const std::string& name)
{
	line_idx p_line = ensure_line(name);
	if (!m_lines[p_line].is_output) 
	{
		m_lines[p_line].is_output = true;
		m_outputs.push_back(p_line);
	}
	return p_line;
}

gate_idx CircuitGraph::add_gate(Gate::Type type, const std::vector<std::string>& input_names, const std::string& output_name)
{
	std::vector<line_idx> inputs;
	for (size_t i = 0; i < input_names.size(); ++i) 
	{
		line_idx p_input = ensure_line(input_names[i]);
		inputs.push_back(p_input);
	}

	line_idx p_output = ensure_line(output_name);

	m_gates.emplace_back(type, p_output, std::move(inputs));
	gate_idx gate = m_gates.size() - 1;
	m_lines[p_output].source = gate;//将新增加的门的索引赋值给输出线的源

	for (size_t i = 0; i < m_gates[gate].get_inputs().size(); ++i) 
	{
		m_lines[m_gates[gate].get_inputs().at(i)].connect_as_input(gate);//将输入线的destination_gates中，插入门的索引
	}

	// Gate validation 并且确定监视值
	// std::vector<int> watching_value;
	// switch(m_gates[gate].get_type()) 
	// {
	// 	case Gate::Type::And:
	// 		for(size_t i = 0; i < m_gates[gate].get_inputs().size(); ++i)
	// 			watching_value.push_back(1);
	// 		watching_value.push_back(0);
	// 		break;
	// 	case Gate::Type::Nand:
	// 		for(size_t i = 0; i < m_gates[gate].get_inputs().size(); ++i)
	// 			watching_value.push_back(1);
	// 		watching_value.push_back(1);
	// 		break;
	// 	case Gate::Type::Or:
	// 		for(size_t i = 0; i < m_gates[gate].get_inputs().size(); ++i)
	// 			watching_value.push_back(0);
	// 		watching_value.push_back(1);
	// 		break;
	// 	case Gate::Type::Nor:
	// 		for(size_t i = 0; i < m_gates[gate].get_inputs().size(); ++i)
	// 			watching_value.push_back(0);
	// 		watching_value.push_back(0);
	// 		assert(m_gates[gate].inputs().size() >= 2);
	// 		break;
	// 	case Gate::Type::Xor:
	// 	case Gate::Type::Xnor:
	// 		assert(m_gates[gate].inputs().size() == 2);
	// 		break;
	// 	case Gate::Type::Not:
	// 	case Gate::Type::Buff:
	// 		assert(m_gates[gate].inputs().size() == 1);
	// 		break;
	// 	default:
	// 		assert(false);
	// }
	return gate;
}

line_idx CircuitGraph::line(const std::string &name)
{
	auto it = m_name_to_line_idx.find(name);

	if (it != m_name_to_line_idx.end())
	{
		return it->second;
	}

	return NULL_INDEX;
}

const line_idx CircuitGraph::get_line(const std::string &name) const
{
	auto it = m_name_to_line_idx.find(name);

	if (it != m_name_to_line_idx.end())
	{
		return it->second;
	}
	return NULL_INDEX;
}

const std::vector<line_idx> &CircuitGraph::get_inputs() const
{
	return m_inputs;
}

const std::vector<line_idx> &CircuitGraph::get_outputs() const
{
	return m_outputs;
}

const std::vector<Gate> &CircuitGraph::get_gates() const
{
	return m_gates;
}

std::vector<Gate> &CircuitGraph::get_gates()
{
	return m_gates;
}

const std::vector<Line> &CircuitGraph::get_lines() const
{
	return m_lines;
}


line_idx CircuitGraph::ensure_line(const std::string& name)
{
	auto it = m_name_to_line_idx.find(name);

	if (it != m_name_to_line_idx.end()) {
		return it->second;
	}

	m_lines.emplace_back();
	Line& line = m_lines.back();

	line.name = name;
	line.id_line = m_lines.size() - 1;

	m_name_to_line_idx[name] = m_lines.size() - 1;

	return line.id_line;
}
