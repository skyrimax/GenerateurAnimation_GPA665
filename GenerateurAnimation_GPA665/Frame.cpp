#include "Frame.h"

// Default constructor
Frame::Frame()
{
}

// Constructor allowing the loading of a frame
// from a list of lines at creation
Frame::Frame(const Vector<std::string>& frameStr, const std::string& path)
{
	// Load frame from list of lines
	load(frameStr, path);
}

// Copy constructor
Frame::Frame(const Frame & frame)
{
	// Copy instructions from frame over to this
	m_instructions = frame.m_instructions;
}

// Move constructor
Frame::Frame(Frame && frame)
{
	// Move instructions from frame over to this
	m_instructions = std::move(frame.m_instructions);
}

// Destructor
Frame::~Frame()
{
}

// Copy assignment operator
Frame & Frame::operator=(const Frame & frame)
{
	// Copy instructions from frame over to this
	m_instructions = frame.m_instructions;

	return *this;
}

// Move assignment operator
Frame & Frame::operator=(Frame && frame)
{
	// Move instructions from frame over to this
	m_instructions = std::move(frame.m_instructions);

	return *this;
}

// Load frame with instrtuctions from a list of lines
bool Frame::load(const Vector<std::string>& frameStr, const std::string& path)
{
	// Unload the frame of it is no already empty
	if (!unload()) {
		return false;
	}

	// Get the number of lines composing the frame
	size_t size = frameStr.size();
	Instruction inst;

	// Run through each line...
	for (size_t i = 0; i < size; ++i) {
		// and load the next instruction with it
		if (inst.load(frameStr[i], path)) {
			// If it is successful, add to this frame's instructions
			m_instructions.push_back(inst);
		}
		else {
			// Else return that an error occurred
			return false;
		}
	}

	// If all goes well, return that no error occurred
	return true;
}

// Unload instructions from frame
bool Frame::unload()
{
	// Clear the list of instructions
	m_instructions.clear();

	// No error should occure
	return true;
}

// Display the frame
bool Frame::display()
{
	// Run through each instruction...
	for (forward_list<Instruction>::iterator it = m_instructions.begin(); it != m_instructions.end(); ++it) {
		// and execute it
		if (!it->exec()) {
			// If an error occurred, return so
			return false;
		}
	}

	// If all goes well, return that no error occurred
	return true;
}
