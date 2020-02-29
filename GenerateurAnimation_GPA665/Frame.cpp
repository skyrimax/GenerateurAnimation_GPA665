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

bool Frame::load(Vector<std::string> frameStr)
{
	if (!unload()) {
		return false;
	}

	size_t size = frameStr.size();
	Instruction inst;

	for (size_t i = 0; i < size; ++i) {
		if (inst.load(frameStr[i])) {
			m_instructions.push_back(inst);
		}
		else {
			return false;
		}
	}
}

bool Frame::unload()
{
	m_instructions.clear();

	return true;
}

bool Frame::display()
{
	for (forward_list<Instruction>::iterator it = m_instructions.begin(); it != m_instructions.end(); it++) {
		if (!it->exec()) {
			return false;
		}
	}

	return true;
}
