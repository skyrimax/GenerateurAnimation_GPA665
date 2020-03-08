#pragma once
#include<string>
#include"forward_list.h"
#include"Instruction.h"
#include"Vector.h"

class Frame
{
public:
	// Constructors and destructor
	Frame();
	Frame(const Vector<std::string>& frameStr);
	Frame(const Frame& frame);
	Frame(Frame&& frame);
	~Frame();

	// Assignment operators
	Frame& operator=(const Frame& frame);
	Frame& operator=(Frame&& frame);

	// Load and unload methods
	bool load(const Vector<std::string>& frameStr);
	bool unload();

	// Methods to display the frame
	bool display();

private:
	forward_list<Instruction> m_instructions;
};

