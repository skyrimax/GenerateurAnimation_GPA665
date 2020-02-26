#include "Frame.h"

Frame::Frame()
{
}

Frame::Frame(Vector<std::string> frameStr)
{
	load(frameStr);
}

Frame::~Frame()
{
}

void Frame::load(Vector<std::string> frameStr)
{
	size_t size = frameStr.size();

	for (size_t i = 0; i < size; ++i) {
		m_instructions.push_back(Instruction(frameStr[i]));
	}
}

void Frame::unload()
{
	m_instructions.clear();
}

void Frame::display()
{
	for (forward_list<Instruction>::iterator it = m_instructions.begin(); it != m_instructions.end(); it++) {
		it->exec();
	}
}
