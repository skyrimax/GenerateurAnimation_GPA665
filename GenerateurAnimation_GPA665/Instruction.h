#pragma once
#include<string>
#include "forward_list.h"
#include "Media.h"

class Instruction
{
public:
	Instruction();
	Instruction(const std::string& line);
	~Instruction();

	bool load(const std::string& line);
	bool unload();

	bool exec();

private:
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