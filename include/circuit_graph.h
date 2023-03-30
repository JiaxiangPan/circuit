#include <string>
#include <cstdint>
#include <limits>
#include <vector>
#include <deque>
#include <set>
#include <unordered_map>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include "log.h"

#ifndef CIRCUIT_GRAPH_H
#define CIRCUIT_GRAPH_H
#pragma once

#define NULL_INDEX -1

using gate_idx = int;
using line_idx = int; 

class Gate;
class CircuitGraph;

struct Line
{
	void connect_as_input(gate_idx gate)
	{
		destination_gates.insert(gate);  //存储线的输出gate
	}
	gate_idx source = NULL_INDEX;         // nullptr means input port
	std::set<gate_idx> destination_gates;
	bool is_input = false;
	bool is_output = false;
	int id_line = NULL_INDEX;
	std::string name;
};

class Gate
{
public:
	enum class Type : uint32_t
	{
		And,
		Nand,
		Or,
		Nor,
		Xor,
		Xnor,
		Not,
		Buff,
		Input,
		Undefined,
	};



	Gate(Type type, line_idx output, std::vector<line_idx> &&inputs);   //构造一般gate

	Type get_type() const { return m_type; }
	Type &type() { return m_type; }

	const std::vector<line_idx> &get_inputs() const { return m_inputs; }
	std::vector<line_idx> &inputs() { return m_inputs; }

	line_idx get_output() const { return m_output; }
	line_idx &output() { return m_output; }


private:
	Type m_type = Type::Undefined;
	std::vector<line_idx> m_inputs;
	line_idx m_output = NULL_INDEX;
};

inline std::ostream& operator<<(std::ostream& os, Gate::Type type) //重载<<运算符
{
switch (type) 
	{
	case Gate::Type::And:
		os << "AND";
		break;
	case Gate::Type::Nand:
		os << "Nand";
		break;
	case Gate::Type::Not:
		os << "Not";
		break;
	case Gate::Type::Or:
		os << "Or";
		break;
	case Gate::Type::Nor:
		os << "Nor";
		break;
	case Gate::Type::Xor:
		os << "Xor";
		break;
	case Gate::Type::Xnor:
		os << "Xnor";
		break;
	case Gate::Type::Buff:
		os << "Buff";
		break;
	case Gate::Type::Undefined:
		os << "Undefined";
		break;
	default:
		os << "???";
		break;
	}
return os;
}

class CircuitGraph
{
public:
	line_idx add_input(const std::string &name);
	line_idx add_output(const std::string &name);
	gate_idx add_gate(Gate::Type type, const std::vector<std::string> &input_names, const std::string &output_name);

	const line_idx get_line(const std::string &name) const;
	line_idx line(const std::string &name);

	const Gate& get_gate(const gate_idx& idx) const { return m_gates[idx]; }
	Gate& gate(const gate_idx& idx) { return m_gates[idx]; }

	const Line& get_line(const line_idx &idx) const { return m_lines[idx]; }
	Line& line(const line_idx &idx) { return m_lines[idx]; }//根据索引来访问访问线Line 进而可以访问struct Line中的成员

	const std::vector<line_idx> &get_inputs() const;
	std::vector<line_idx> &inputs() { return m_inputs; }
	
	const std::vector<line_idx> &get_outputs() const;
	std::vector<line_idx> &outputs() { return m_outputs; }

	const std::vector<Gate> &get_gates() const;
	std::vector<Gate> &get_gates();
	
	const std::vector<Line> &get_lines() const;
	std::vector<Line> &lines() { return m_lines; }

	line_idx ensure_line(const std::string &name);

	int total_line_number() { return m_name_to_line_idx.size(); }
	//无论是单纯的输入输出还是中间连线都是经过ensure_line来添加index，ensure_line又用到了m_name_toline_index。故可以返回所有连线的数量
private:
	std::vector<Line> m_lines;
	std::vector<Gate> m_gates;

	std::vector<line_idx> m_inputs;
	std::vector<line_idx> m_outputs;

	std::unordered_map<std::string, line_idx> m_name_to_line_idx; //存储了所有的name及其对应的index
};
#endif