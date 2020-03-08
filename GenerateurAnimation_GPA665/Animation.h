#pragma once
#include "List.h"
#include "Frame.h"

class Animation
{
public:
	// Constructors and destructor
	Animation();
	Animation(const char *sScriptFile);
	Animation(const Animation& animation);
	Animation(Animation&& animation);
	~Animation();

	// Assignment operators
	Animation& operator=(const Animation& animation);
	Animation& operator=(Animation&& animation);

	// Load and unload methods
	bool load(const char *sScriptFile);
	bool unload();

	// Play forward and backward methods
	bool playForward();
	bool playBackward();

private:
	// States for the finite state transducer used
	// to parse the script file and load the animation
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

