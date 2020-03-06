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

Animation::Animation(const Animation & animation)
{
	m_frames = animation.m_frames;
	m_initFrame = animation.m_initFrame;
}

Animation::Animation(Animation && animation)
{
	m_frames = std::move(animation.m_frames);
	m_initFrame = std::move(animation.m_initFrame);
}

Animation::~Animation()
{
}

Animation & Animation::operator=(const Animation & animation)
{
	m_frames = animation.m_frames;
	m_initFrame = animation.m_initFrame;

	return *this;
}

Animation & Animation::operator=(Animation && animation)
{
	m_frames = std::move(animation.m_frames);
	m_initFrame = std::move(animation.m_initFrame);

	return *this;
}

bool Animation::load(const char * sScriptFile)
{
	std::fstream script(sScriptFile);
	std::string line;
	Vector<std::string>lines;
	Frame fr;

	FSTParserState state = FSTParserState::Start;
	bool ret = false;

	std::string init("INIT");
	std::string frame("FRAME");
	std::string end("END");

	if (!script.is_open()) {
		return false;
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
				if (m_initFrame.load(lines)) {
					state = FSTParserState::Frame;
					lines.clear();
				}
				else {
					state = FSTParserState::Err;
				}
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
				if (fr.load(lines)) {
					m_frames.push_back(fr);
					lines.clear();
				}
				else {
					state = FSTParserState::Err;
				}
			}
			else if (line.find(end) != std::string::npos) {
				if (fr.load(lines)) {
					m_frames.push_back(Frame(lines));
					ret = true;
					state = FSTParserState::End;
				}
				else {
					state = FSTParserState::Err;
				}
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

	return ret;
}

bool Animation::unload()
{
	m_frames.clear();
	m_initFrame.unload();

	return true;
}

bool Animation::playForward()
{
	if (!m_initFrame.display()) {
		return false;
	}

	for (list<Frame>::iterator it = m_frames.begin(); it != m_frames.end(); it++) {
		if (!it->display()) {
			return false;
		}
	}

	return true;
}

bool Animation::playBackward()
{
	if (!m_initFrame.display()) {
		return false;
	}

	for (list<Frame>::backward_iterator it = m_frames.rbegin(); it != m_frames.rend(); it++) {
		if (!it->display()) {
			return false;
		}
	}

	return true;
}
