#pragma once
#include<string>
#include "forward_list.h"
#include "Media.h"

class Instruction
{
public:
	Instruction();
	Instruction(std::string line);
	~Instruction();

	void load(std::string line);
	void unload();

	void exec();

private:

	void (*func)(Parameters params);
	Parameters m_params;
};

	void dummyFunc(Parameters params);