#include "Instruction.h"
#include <cstring>
#include <sstream>

Instruction::Instruction()
{
	func = dummyFunc;

	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}
}

Instruction::Instruction(std::string line)
{
	load(line);
}

Instruction::~Instruction()
{
}

void Instruction::load(std::string line)
{
	strcpy(m_params.String, line.c_str());

	std::stringstream stream(line);


}

void Instruction::unload()
{
	func = dummyFunc;

	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}
}

void Instruction::exec()
{
	func(m_params);
}

void dummyFunc(Parameters params)
{
}
