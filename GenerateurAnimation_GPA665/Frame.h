#pragma once
#include<string>
#include"forward_list.h"
#include"Instruction.h"
#include"Vector.h"

class Frame
{
public:
	Frame();
	Frame(const Vector<std::string>& frameStr);
	Frame(const Frame& frame);
	Frame(Frame&& frame);
	~Frame();

	Frame& operator=(const Frame& frame);
	Frame& operator=(Frame&& frame);

	bool load(const Vector<std::string>& frameStr);
	bool unload();

	bool display();

private:
	forward_list<Instruction> m_instructions;
};

