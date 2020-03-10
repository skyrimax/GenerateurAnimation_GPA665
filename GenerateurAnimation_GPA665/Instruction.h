#pragma once
#include<string>
#include "forward_list.h"
#include "Media.h"

class Instruction
{
public:
	// Constructors and destructor
	Instruction();
	Instruction(const std::string& line, const std::string& path);
	Instruction(const Instruction& instruction);
	Instruction(Instruction&& instruction);
	~Instruction();

	// Assignment operators
	Instruction& operator=(const Instruction& instruction);
	Instruction& operator=(Instruction&& instruction);

	// Load and unload methods
	bool load(const std::string& line, const std::string& path);
	bool unload();

	// Method to execute the instruction with the parameters
	bool exec();

private:
	// Convenience functions load each instruction and it's parameters
	bool setcbru(std::stringstream& stream, const std::string& path);
	bool setcpen(std::stringstream& stream, const std::string& path);
	bool setdcir(std::stringstream& stream, const std::string& path);
	bool setdell(std::stringstream& stream, const std::string& path);
	bool setdlin(std::stringstream& stream, const std::string& path);
	bool setdpnt(std::stringstream& stream, const std::string& path);
	bool setdrec(std::stringstream& stream, const std::string& path);
	bool setdsqr(std::stringstream& stream, const std::string& path);
	bool setdtxt(std::stringstream& stream, const std::string& path);
	bool seteras(std::stringstream& stream, const std::string& path);
	bool setmsnd(std::stringstream& stream, const std::string& path);
	bool setwait(std::stringstream& stream, const std::string& path);
	bool setdummy(std::stringstream& stream, const std::string& path);

	bool (*func)(Parameters* params);
	Parameters m_params;
};

	bool dummyFunc(Parameters* params);