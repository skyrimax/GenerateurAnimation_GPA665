#include "Animation.h"
#include <fstream>
#include "Vector.h"

Animation::Animation()
{
}

Animation::Animation(const char * sScriptFile)
{
	load(sScriptFile);
}

Animation::~Animation()
{
}

void Animation::load(const char * sScriptFile)
{
	std::fstream script(sScriptFile);
	std::string line;
	Vector<std::string>lines;

	FSTParserState state = FSTParserState::Start;

	std::string init("INIT");
	std::string frame("FRAME");
	std::string end("END");

	if (!script.is_open()) {
		return;
	}

	while (state!=FSTParserState::Err && state!=FSTParserState::End && std::getline(script, line)) {
		switch (state)
		{
		case Animation::FSTParserState::Start:
			if (line.find(init) == std::string::npos &&
				line.find(frame) == std::string::npos &&
				line.find(end) == std::string::npos) {
				state = FSTParserState::Title;
			}
			else {
				state = FSTParserState::Err;
			}
			break;
		case Animation::FSTParserState::Title:
			if (line.find(frame) != std::string::npos && line.find(end) != std::string::npos) {
				state = FSTParserState::Err;
			}
			else if (line.find(init)!=std::string::npos) {
				state = FSTParserState::Init;
			}
			break;
		case Animation::FSTParserState::Init:
			if (line.find(init) != std::string::npos && line.find(end) != std::string::npos) {
				state = FSTParserState::Err;
			}
			else if (line.find(frame) != std::string::npos) {
				state = FSTParserState::Frame;
				m_initFrame.load(lines);
				lines.clear();
			}
			else {
				lines.push_back(line);
			}
			break;
		case Animation::FSTParserState::Frame:
			if (line.find(init) != std::string::npos) {
				state = FSTParserState::Err;
			}
			else if (line.find(frame) != std::string::npos) {
				m_frames.push_back(Frame(lines));
				lines.clear();
			}
			else if (line.find(end) != std::string::npos) {
				state = FSTParserState::End;
			}
			else {
				lines.push_back(line);
			}
			break;
		case Animation::FSTParserState::Err:
			state = FSTParserState::End;
			break;
		case Animation::FSTParserState::End:
			break;
		default:
			break;
		}
	}
}

void Animation::unload()
{
	m_frames.clear();

	m_initFrame.unload();
}

void Animation::playForward()
{
	m_initFrame.display();

	for (list<Frame>::iterator it = m_frames.begin(); it != m_frames.end(); it++) {
		it->display();
	}
}

void Animation::playBackward()
{
	m_initFrame.display();

	for (list<Frame>::backward_iterator it = m_frames.rbegin(); it != m_frames.rend(); it++) {
		it->display();
	}
}
