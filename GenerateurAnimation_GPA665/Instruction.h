#pragma once
#include<string>
#include "forward_list.h"
#include "Media.h"

class Instruction
{
public:
	// Constructors and destructor
	Instruction();
	Instruction(const std::string& line);
	Instruction(const Instruction& instruction);
	Instruction(Instruction&& instruction);
	~Instruction();

	// Assignment operators
	Instruction& operator=(const Instruction& instruction);
	Instruction& operator=(Instruction&& instruction);

	// Load and unload methods
	bool load(const std::string& line);
	bool unload();

	// Method to execute the instruction with the parameters
	bool exec();

private:
	// Convenience functions load each instruction and it's parameters
	bool setcbru(std::stringstream& stream);
	bool setcpen(std::stringstream& stream);
	bool setdcir(std::stringstream& stream);
	bool setdell(std::stringstream& stream);
	bool setdlin(std::stringstream& stream);
	bool setdpnt(std::stringstream& stream);
	bool setdrec(std::stringstream& stream);
	bool setdsqr(std::stringstream& stream);
	bool setdtxt(std::stringstream& stream);
	bool seteras(std::stringstream& stream);
	bool setmsnd(std::stringstream& stream);
	bool setwait(std::stringstream& stream);
	bool setdummy(std::stringstream& stream);

	bool (*func)(Parameters* params);
	Parameters m_params;
};

	bool dummyFunc(Parameters* params);