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

	void load(Vector<std::string> frameStr);
	void unload();

	void display();

private:
	forward_list<Instruction> m_instructions;
};

