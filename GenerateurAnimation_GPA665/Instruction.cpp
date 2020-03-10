#include "Instruction.h"
#include <cstring>
#include <string>
#include <sstream>
#include <execution>
#include <iostream>

// Default constructor
Instruction::Instruction()
{
	// func points on function that does nothing
	func = dummyFunc;

	// all parameters are initialised
	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}
}

// Constructor allowing the loading of an intructions at construction
Instruction::Instruction(const std::string& line)
{
	// Load the instruction from a line
	load(line);
}

// Copy constructor
Instruction::Instruction(const Instruction & instruction)
{
	// Copy the function from instruction to this
	func = instruction.func;
	// Copy the parameters from instruction to this
	m_params = instruction.m_params;
}

// Move constructor
Instruction::Instruction(Instruction && instruction)
{
	// Copy the function from instruction to this
	func = instruction.func;
	// Copy the parameters from instruction to this
	m_params = instruction.m_params;
}

// Destructor
Instruction::~Instruction()
{
}

// Copy assignmenet operator
Instruction & Instruction::operator=(const Instruction & instruction)
{
	// Copy the function from instruction to this
	func = instruction.func;
	// Copy the parameters from instruction to this
	m_params = instruction.m_params;

	return *this;
}

// Move assignmenet operator
Instruction & Instruction::operator=(Instruction && instruction)
{
	// Copy the function from instruction to this
	func = instruction.func;
	// Copy the parameters from instruction to this
	m_params = instruction.m_params;

	return *this;
}

// Load the instruction from a line
bool Instruction::load(const std::string& line)
{
	// Unload the instruction if it is not already empty
	unload();

	std::string data;

	// Open a stream from the line to make parsing easier
	std::stringstream stream(line);

	// Extract the first word, should be an instruction
	stream >> data;

	// Based on the instruction, select the appropriate
	// loading function for it and it's parameters
	if (data == std::string("cbru")) {
		return setcbru(stream);
	}
	else if (data == std::string("cpen")) {
		return setcpen(stream);
	}
	else if (data == std::string("dcir")) {
		return setdcir(stream);
	}
	else if (data == std::string("dell")) {
		return setdell(stream);
	}
	else if (data == std::string("dlin")) {
		return setdlin(stream);
	}
	else if (data == std::string("dpnt")) {
		return setdpnt(stream);
	}
	else if (data == std::string("drec")) {
		return setdrec(stream);
	}
	else if (data == std::string("dsqr")) {
		return setdsqr(stream);
	}
	else if (data == std::string("dtxt")) {
		return setdtxt(stream);
	}
	else if (data == std::string("eras")) {
		return seteras(stream);
	}
	else if (data == std::string("msnd")) {
		return setmsnd(stream);
	}
	else if (data == std::string("wait")) {
		return setwait(stream);
	}
	// if the instruction is not recognized, load a dummy function
	else {
		return setdummy(stream);
	}

	// if an error occured, signal so
	return false;
}

// Unload the instruction
bool Instruction::unload()
{
	// func points on function that does nothing
	func = dummyFunc;

	// all parameters are reset
	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}

	// Shouldn't fail
	return true;
}

// Execute the instruction with the parameters
bool Instruction::exec()
{
	return func(&m_params);
}

// Function that does nothing
bool dummyFunc(Parameters* params)
{
	// Always works (a rare feat in programming)
	return true;
}

// Set function and parameters for cbru
bool Instruction::setcbru(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	// set function
	func = Media_SetBrushColor;

	// Will extract the 3 parameters
	for (int i = 0; i < 3; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for cpen
bool Instruction::setcpen(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	// set function
	func = Media_SetPenColor;

	// Will extract the 3 parameters
	for (int i = 0; i < 3; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dcir
bool Instruction::setdcir(std::stringstream & stream)
{
	int val[3];
	std::string data;
	m_params.NbrParam = 4;

	// set function
	func = Media_DrawEllipse;

	// Will extract the 3 parameters
	for (int i = 0; i < 3; i++) {
		try {
			// extract the parameter and store in temporary array as a number
			stream >> data;
			val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// Set corner (x1, y1)
	m_params.Val[0] = val[0] - val[2];
	m_params.Val[1] = val[1] - val[2];
	// Set corner (x2, y2)
	m_params.Val[2] = val[0] + val[2];
	m_params.Val[3] = val[1] + val[2];

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dell
bool Instruction::setdell(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	// set function
	func = Media_DrawEllipse;

	// Will extract the 4 parameters
	for (int i = 0; i < 4; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dlin
bool Instruction::setdlin(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	// set function
	func = Media_DrawLine;

	// Will extract the 4 parameters
	for (int i = 0; i < 4; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dpnt
bool Instruction::setdpnt(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 2;

	// set function
	func = Media_DrawPixel;

	// Will extract the 2 parameters
	for (int i = 0; i < 2; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for drect
bool Instruction::setdrec(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	// set function
	func = Media_DrawRect;

	// Will extract the 4 parameters
	for (int i = 0; i < 4; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dsqr
bool Instruction::setdsqr(std::stringstream & stream)
{
	int val[3];
	std::string data;
	m_params.NbrParam = 4;

	// set function
	func = Media_DrawRect;

	// Will extract the 3 parameters
	for (int i = 0; i < 3; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// Set corner (x1, y1)
	m_params.Val[0] = val[0] - val[2] / 2;
	m_params.Val[1] = val[1] - val[2] / 2;
	// Set corner (x2, y2)
	m_params.Val[2] = val[0] + val[2] / 2;
	m_params.Val[3] = val[1] + val[2] / 2;

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dtxt
bool Instruction::setdtxt(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	// set function
	func = Media_TextOut;

	// Will extract the 2 first parameters
	for (int i = 0; i < 2; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	try {
		// Extract the message to be displayed and store in the string of m_params
		stream >> data;
		strcpy_s(m_params.String, sizeof m_params.String, data.c_str());
	}
	catch (std::exception& e) {
		// if the parameters is not available, return that an error occured
		std::cerr << e.what() << '\n';
		return false;
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for eras
bool Instruction::seteras(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	// set function
	func = Media_Clear;

	// Will extract the 3 parameters
	for (int i = 0; i < 3; i++) {
		try {
			// extract the parameter and store in array as a number
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			// if a parameters is not available, return that an error occured
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for msnd
bool Instruction::setmsnd(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 1;

	// set function
	func = Media_PlaySound;

	try {
		// Extract the name of the sound file to be played and store in the string of m_params
		stream >> data;
		strcpy_s(m_params.String, sizeof m_params.String, data.c_str());
	}
	catch (std::exception& e) {
		// if the parameters is not available, return that an error occured
		std::cerr << e.what() << '\n';
		return false;
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for wait
bool Instruction::setwait(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 1;

	// set function
	func = Media_Delay;

	try {
		// extract the parameter and store in array as a number
		stream >> data;
		m_params.Val[0] = std::stoi(data);
	}
	catch (std::exception& e) {
		// if the parameters is not available, return that an error occured
		std::cerr << e.what() << '\n';
		return false;
	}

	// Return an error if there are parameters remaining in the line
	if (!stream.eof()) {
		return false;
	}

	// If all goes well, signal that no error occured
	return true;
}

// Set function and parameters for dummy function
bool Instruction::setdummy(std::stringstream & stream)
{
	// set function
	func = dummyFunc;

	// Set all parameters to default values
	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}

	// Shouldn't fail
	return true;
}
