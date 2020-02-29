#pragma once
#include<string>
#include"forward_list.h"
#include"Instruction.h"
#include"Vector.h"

class Frame
{
public:
	Frame();
	Frame(Vector<std::string> frameStr);
	~Frame();

	bool load(Vector<std::string> frameStr);
	bool unload();

	bool display();

private:
	forward_list<Instruction> m_instructions;
};

