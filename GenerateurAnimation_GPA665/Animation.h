#pragma once
#include "List.h"
#include "Frame.h"

class Animation
{
public:
	Animation();
	Animation(const char *sScriptFile);
	~Animation();

	bool load(const char *sScriptFile);
	bool unload();

	bool playForward();
	bool playBackward();

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

