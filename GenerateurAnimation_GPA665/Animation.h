#pragma once
#include "List.h"
#include "Frame.h"

class Animation
{
public:
	Animation();
	Animation(const char *sScriptFile);
	~Animation();

	void load(const char *sScriptFile);
	void unload();

	void playForward();
	void playBackward();

private:
	enum class FSTParserState {
		Start,
		Title,
		Init,
		Frame,
		Err,
		End,
	};

	list<Frame> m_frames;
	Frame m_initFrame;
};

