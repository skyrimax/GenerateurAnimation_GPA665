#include "Instruction.h"
#include <cstring>
#include <string>
#include <sstream>
#include <execution>
#include <iostream>

Instruction::Instruction()
{
	func = dummyFunc;

	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}
}

Instruction::Instruction(std::string line)
{
	load(line);
}

Instruction::~Instruction()
{
}

bool Instruction::load(std::string line)
{
	std::string data;

	std::stringstream stream(line);

	stream >> data;

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
	else {
		return setdummy(stream);
	}

	return false;
}

bool Instruction::unload()
{
	func = dummyFunc;

	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}

	return true;
}

bool Instruction::exec()
{
	return func(&m_params);
}

bool dummyFunc(Parameters* params)
{
}

bool Instruction::setcbru(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	func = Media_SetBrushColor;

	for (int i = 0; i < 3; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setcpen(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	func = Media_SetPenColor;

	for (int i = 0; i < 3; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdcir(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	func = Media_DrawEllipse;

	for (int i = 0; i < 3; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	m_params.Val[3] = m_params.Val[2];

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdell(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	func = Media_DrawEllipse;

	for (int i = 0; i < 4; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdlin(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	func = Media_DrawLine;

	for (int i = 0; i < 4; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdpnt(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 2;

	func = Media_DrawPixel;

	for (int i = 0; i < 2; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdrec(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	func = Media_DrawRect;

	for (int i = 0; i < 4; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdsqr(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 4;

	func = Media_DrawRect;

	for (int i = 0; i < 3; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	m_params.Val[3] = m_params.Val[2];

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdtxt(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	func = Media_TextOut;

	for (int i = 0; i < 2; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	try {
		stream >> data;
		strcpy(m_params.String, data.c_str());
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::seteras(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 3;

	func = Media_Clear;

	for (int i = 0; i < 3; i++) {
		try {
			stream >> data;
			m_params.Val[i] = std::stoi(data);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setmsnd(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 1;

	func = Media_PlaySound;

	try {
		stream >> data;
		strcpy(m_params.String, data.c_str());
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setwait(std::stringstream & stream)
{
	std::string data;
	m_params.NbrParam = 1;

	func = Media_PlaySound;

	try {
		stream >> data;
		m_params.Val[0] = std::stoi(data);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}

	if (!stream.rdbuf()->in_avail()) {
		return false;
	}

	return true;
}

bool Instruction::setdummy(std::stringstream & stream)
{
	func = dummyFunc;

	m_params.NbrParam = 0;
	m_params.String[0] = '\0';
	for (int i = 0; i < 8; ++i) {
		m_params.Val[i] = 0;
	}

	return true;
}
